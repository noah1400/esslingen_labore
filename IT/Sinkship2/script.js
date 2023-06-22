// Run only when the page is fully loaded
window.onload = function () {
    ship.init();
};

let ship = {

    pfield: null,
    cfield: null,
    inventory: [],
    selectedShip: null,

    // init
    init: function () {
        document.body.appendChild(this.makeHeader());
        document.body.appendChild(this.makeMain());
        document.body.appendChild(this.makeFooter());
        this.fillInventory();
        this.addShipPlacementHandler(this.pfield);
    },
    makeHeader: function () {
        let header = document.createElement('header');
        let limiter = this.makeLimiter();
        header.appendChild(limiter);
        let headline = document.createElement('h1');
        headline.innerHTML = 'Sinkship';
        limiter.appendChild(headline);
        let copyrigth = document.createElement('p');
        copyrigth.innerHTML = 'by Noah Scholz'
        limiter.appendChild(copyrigth);
        return header;
    },
    makeMain: function () {
        let main = document.createElement('main');
        let limiter = this.makeLimiter();
        let ctrls = this.makeControls();
        let fields = this.makeDiv('fields');
        this.pfield = this.makeField('playerfield');
        this.cfield = this.makeField('computerfield');
        fields.appendChild(this.pfield.field);
        //fields.appendChild(this.cfield.field);
        let buildMenu = this.makeBuildMenu();
        fields.appendChild(buildMenu);
        limiter.appendChild(ctrls);
        limiter.appendChild(fields);
        main.appendChild(limiter);
        return main;
    },
    makeControls: function () {
        let ctrls = this.makeDiv('controls');
        let btn1 = this.makeButton('Build');
        let btn2 = this.makeButton('Play');
        ctrls.appendChild(btn1);
        ctrls.appendChild(btn2);
        return ctrls;
    },
    makeButton: function (label) {
        let btn = document.createElement('button');
        btn.innerHTML = label;
        return btn;
    },
    makeFooter: function () {
        let footer = document.createElement('footer');
        let limiter = this.makeLimiter();
        footer.appendChild(limiter);
        let copyrigth = document.createElement('p');
        copyrigth.innerHTML = 'by Noah Scholz'
        limiter.appendChild(copyrigth);
        return footer;
    },
    makeLimiter: function () {
        let limiter = this.makeDiv('limiter');
        return limiter;
    },
    makeDiv: function (className) {
        let div = document.createElement('div');
        div.classList.add(className);
        return div;
    },
    makeField: function (id) {
        let field = this.makeDiv('field');
        let cells = [];
        field.id = id;
        for (let y = 0; y < 10; y++) {
            for (let x = 0; x < 10; x++) {
                let cell = this.makeDiv('cell');
                cell.id = id + '_' + x + '_' + y;
                field.appendChild(cell);
                cells.push(
                    {
                        element: cell,
                        used: false,
                    }
                );
            }
        }
        return {
            field,
            cells,
            getCell: function (x, y) {
                return cells[x + y * 10]; // get cell by x and y
            },
            isCellValid: function (x, y) {
                const dimension = 10;
                return x >= 0 && x < dimension && y >= 0 && y < dimension;
            }
        };
    },
    fillInventory: function () {
        this.inventory = [];
        const shipData = [
            { type: 'Battleship', size: 5, hits: [false, false, false, false, false] },
            { type: 'Cruiser', size: 4, hits: [false, false, false, false] },
            { type: 'Cruiser', size: 4, hits: [false, false, false, false] },
            { type: 'Destroyer', size: 3, hits: [false, false, false] },
            { type: 'Destroyer', size: 3, hits: [false, false, false] },
            { type: 'Destroyer', size: 3, hits: [false, false, false] },
            { type: 'Submarine', size: 2, hits: [false, false] },
            { type: 'Submarine', size: 2, hits: [false, false] },
            { type: 'Submarine', size: 2, hits: [false, false] },
            { type: 'Submarine', size: 2, hits: [false, false] }
        ];

        shipData.forEach(ship => {
            const newShip = {
                ...ship,
                orientation: '',
                x: 0,
                y: 0,
                placed: false
            };
            this.inventory.push(newShip);
        });
    },
    updatePlacementCells: function () {
        const remaining = this.remainingShips();

        for (const type in remaining) {
            const className1 = type.toLowerCase() + '-h';
            const className2 = type.toLowerCase() + '-v';

            [className1, className2].forEach(className => {
                const elements = document.getElementsByClassName(className);

                for (const element of elements) {
                    element.classList.toggle('selectable', remaining[type] > 0);
                    element.classList.toggle('noRemaining', remaining[type] <= 0);
                }
            });
        }
    },
    remainingShips: function () {
        const remaining = {}

        for (const ship of this.inventory) {
            if (!ship.placed) {
                if (ship.type in remaining) {
                    remaining[ship.type]++;
                } else {
                    remaining[ship.type] = 1;
                }
            }
        }

        // Fill with zeros
        for (const ship of this.inventory) {
            if (ship.type in remaining) {
                continue;
            }
            remaining[ship.type] = 0;
        }

        return remaining;
    },
    getNextFreeShip: function (type, size, orientation) {
        let ship = this.inventory.find(ship => ship.type === type && ship.placed === false && ship.size === size);
        if (ship) {
            ship.orientation = orientation;
        }
        return ship;
    },
    launchShip: function (field, x, y, length, orientation) {
        const ship = [];

        for (let i = 0; i < length; i++) {
            const cell = field.getCell(x, y);

            const classList = ['left', 'top', 'right', 'bottom', 'horizontal', 'vertical'];
            const classIndex = (i === 0) ? (orientation === 'h' ? 0 : 1) : (i === length - 1) ? (orientation === 'h' ? 2 : 3) : (orientation === 'h' ? 4 : 5);
            cell.element.classList.add(classList[classIndex]);

            cell.used = true;
            ship.push(cell);

            if (orientation === 'h') {
                x++;
            } else {
                y++;
            }
        }

        return ship;
    },
    makeBuildMenu: function () {
        let menu = this.makeDiv('field');
        menu.id = 'computerfield';
        let table = document.createElement('table');
        menu.appendChild(table);
        let head = this.makeTableHeader([
            'Number',
            '',
            '',
            'Type',
            'Size']);
        table.appendChild(head);

        let rows = [
            {
                number: 1,
                cssnms1: ['battleship-h', 'selectable'],
                cssnms2: ['battleship-v', 'selectable'],
                type: 'Battleship',
                size: 5,
            },
            {
                number: 2,
                cssnms1: ['cruiser-h', 'selectable'],
                cssnms2: ['cruiser-v', 'selectable'],
                type: 'Cruiser',
                size: 4,
            },
            {
                number: 3,
                cssnms1: ['destroyer-h', 'selectable'],
                cssnms2: ['destroyer-v', 'selectable'],
                type: 'Destroyer',
                size: 3,
            },
            {
                number: 4,
                cssnms1: ['submarine-h', 'selectable'],
                cssnms2: ['submarine-v', 'selectable'],
                type: 'Submarine',
                size: 2,
            }
        ];

        let body = document.createElement('tbody');
        table.appendChild(body);
        for (let i = 0; i < rows.length; i++) {
            let row = document.createElement('tr');
            let cell = document.createElement('td');
            cell.innerHTML = rows[i].number;
            row.appendChild(cell);
            cell = document.createElement('td');
            cell.classList.add(rows[i].cssnms1[0]);
            cell.classList.add(rows[i].cssnms1[1]);

            let self = this;
            cell.addEventListener('click', function () {
                let ship = self.getNextFreeShip(rows[i].type, rows[i].size, 'h');
                self.clearUsableCells(self.pfield);
                if (ship) {
                    self.colorUsableCells(self.pfield, rows[i].size, 'h');
                } else {
                    self.resetCells(self.pfield);
                }
                self.selectedShip = ship;
                console.log(self.selectedShip);
            });

            row.appendChild(cell);
            cell = document.createElement('td');
            cell.classList.add(rows[i].cssnms2[0]);
            cell.classList.add(rows[i].cssnms2[1]);

            cell.addEventListener('click', function () {
                let ship = self.getNextFreeShip(rows[i].type, rows[i].size, 'v');
                self.clearUsableCells(self.pfield);
                if (ship) {
                    self.colorUsableCells(self.pfield, rows[i].size, 'v');
                } else {
                    self.resetCells(self.pfield);
                }
                self.selectedShip = ship;
            });

            row.appendChild(cell);
            cell = document.createElement('td');
            cell.innerHTML = rows[i].type;
            row.appendChild(cell);
            cell = document.createElement('td');
            cell.innerHTML = rows[i].size;
            row.appendChild(cell);
            body.appendChild(row);
        }
        return menu;
    },
    makeTableHeader: function (content) {
        // content is an array of strings
        let head = document.createElement('thead');
        let row = document.createElement('tr');
        for (let i = 0; i < content.length; i++) {
            let cell = document.createElement('th');
            cell.innerHTML = content[i];
            row.appendChild(cell);
        }
        head.appendChild(row);
        return head;
    },
    getUsableCells: function (field, size, orientation) {
        const usableCells = [];
        const dimension = 10;
        const checkAxis = orientation === 'h' ? 'x' : 'y';

        for (let y = 0; y < dimension; y++) {
            for (let x = 0; x < dimension; x++) {
                const cell = field.getCell(x, y);
                if (!cell.used) {
                    let enoughSpace = true;
                    let validPosition = true;

                    if (checkAxis === 'x') {
                        enoughSpace = x + size <= dimension;
                        for (let i = 0; i < size && enoughSpace; i++) {
                            const neighborCell = field.getCell(x + i, y);
                            if (neighborCell.used || this.hasNeighborShip(field, x + i, y)) {
                                enoughSpace = false;
                                validPosition = false;
                                break;
                            }
                        }
                    } else {
                        enoughSpace = y + size <= dimension;
                        for (let i = 0; i < size && enoughSpace; i++) {
                            const neighborCell = field.getCell(x, y + i);
                            if (neighborCell.used || this.hasNeighborShip(field, x, y + i)) {
                                enoughSpace = false;
                                validPosition = false;
                                break;
                            }
                        }
                    }

                    if (enoughSpace && validPosition) {
                        usableCells.push({ x, y });
                        cell.element.classList.add('usable');
                    }
                }
            }
        }

        return usableCells;
    },
    hasNeighborShip: function (field, x, y) {
        const neighbors = [
            { dx: -1, dy: 0 },  // left
            { dx: 1, dy: 0 },   // right
            { dx: 0, dy: -1 },  // top
            { dx: 0, dy: 1 },   // bottom
        ];

        for (const neighbor of neighbors) {
            const nx = x + neighbor.dx;
            const ny = y + neighbor.dy;
            if (field.isCellValid(nx, ny) && field.getCell(nx, ny).used) {
                return true;
            }
        }

        return false;
    },
    colorUsableCells: function (field, size, orientation) {
        this.getUsableCells(field, size, orientation).forEach(({ x, y }) => {
            const cell = field.getCell(x, y);
            cell.element.classList.add('usable');
            cell.element.classList.remove('disabled');
        });
    },

    clearUsableCells: function (field) {
        field.cells.forEach(cell => {
            cell.element.classList.remove('usable');
            cell.element.classList.add('disabled');
        });
    },

    resetCells: function (field) {
        field.cells.forEach(cell => {
            cell.element.classList.remove('usable');
            cell.element.classList.remove('disabled');
        });
    },
    addShipPlacementHandler: function (field) {
        let cells = field.cells;
        let self = this; // Store outer 'this' reference

        for (let i = 0; i < cells.length; i++) {
            let cell = cells[i];
            cell.element.addEventListener('click', function () {
                let x = i % 10;
                let y = Math.floor(i / 10);
                self.placementHandler(x, y, self.selectedShip); // Use the stored 'this' reference
            });
        }
    },
    getShipAtPosition: function (x, y) {
        for (const ship of this.inventory) {
            if (ship.placed && ((ship.x === x && ship.y === y) ||
                (ship.orientation === 'h' && y === ship.y && x >= ship.x && x < ship.x + ship.size) ||
                (ship.orientation === 'v' && x === ship.x && y >= ship.y && y < ship.y + ship.size))) {
                return ship;
            }
        }
        return null;
    },
    removeShip: function (field, ship) {
        for (let i = 0; i < ship.size; i++) {
            const x = ship.orientation === 'h' ? ship.x + i : ship.x;
            const y = ship.orientation === 'v' ? ship.y + i : ship.y;
            const cell = field.getCell(x, y);
            cell.element.classList = ["cell"];
            cell.used = false;
        }
    },
    placementHandler: function (x, y, ship) {

        if (ship && this.pfield.getCell(x, y).element.classList.contains('usable')) {
            ship.placed = true;
            ship.x = x;
            ship.y = y;
            this.launchShip(this.pfield, x, y, ship.size, ship.orientation);
            this.resetCells(this.pfield);
            this.selectedShip = null;
            this.updatePlacementCells();
        } else if (!ship) {
            let ship = this.getShipAtPosition(x, y);
            if (ship) {
                this.removeShip(this.pfield, ship);
                ship.placed = false;
                this.updatePlacementCells();
            }
        }
    },
};