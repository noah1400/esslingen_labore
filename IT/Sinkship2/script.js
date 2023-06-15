// Run only when the page is fully loaded
window.onload = function() {
    ship.init();
};

let ship = {

    pfield : null,
    cfield : null,

    // init
    init: function() {
        document.body.appendChild(this.makeHeader());
        document.body.appendChild(this.makeMain());
        document.body.appendChild(this.makeFooter());
        this.launchShip(this.pfield, 1, 1, 4, 'h');
        this.addShipPlacementHandler(this.pfield);
    },
    makeHeader: function() {
        let header =  document.createElement('header');
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
    makeMain: function() {
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
    makeControls: function() {
        let ctrls = this.makeDiv('controls');
        let btn1 = this.makeButton('Build');
        let btn2 = this.makeButton('Play');
        ctrls.appendChild(btn1);
        ctrls.appendChild(btn2);
        return ctrls;
    },
    makeButton: function(label) {
        let btn = document.createElement('button');
        btn.innerHTML = label;
        return btn;
    },
    makeFooter: function() {
        let footer = document.createElement('footer');
        let limiter = this.makeLimiter();
        footer.appendChild(limiter);
        let copyrigth = document.createElement('p');
        copyrigth.innerHTML = 'by Noah Scholz'
        limiter.appendChild(copyrigth);
        return footer;
    },
    makeLimiter: function() {
        let limiter = this.makeDiv('limiter');
        return limiter;
    },
    makeDiv: function(className) {
        let div = document.createElement('div');
        div.classList.add(className);
        return div;
    },
    makeField: function(id) {
        let field = this.makeDiv('field');
        let cells = [];
        field.id = id;
        for (let y = 0; y < 10; y++) {
            for(let x = 0; x < 10; x++) {
                let cell = this.makeDiv('cell');
                cell.id = id + '_' + x + '_' + y;
                field.appendChild(cell);
                cells.push(cell);
            }
        }
        return {
            field,
            cells,
            getCell: function(x, y) {
                return cells[x + y * 10]; // get cell by x and y
            },
        };
    },
    launchShip: function(field, x, y, length, direction) {
        let ship = [];
        for (let i = 0; i < length; i++) {
            let cell = field.getCell(x, y);
            if (i === 0){
                if (direction === 'h') {
                    cell.classList.add('left');
                } else {
                    cell.classList.add('top');
                }
            } else if (i === length - 1) {
                if (direction === 'h') {
                    cell.classList.add('right');
                } else {
                    cell.classList.add('bottom');
                }
            } else {
                if (direction === 'h') {
                    cell.classList.add('horizontal');
                } else {
                    cell.classList.add('vertical');
                }
            }
            cell.used = true;
            ship.push(cell);
            if (direction === 'h') {
                x++;
            } else {
                y++;
            }
        }
        return ship;
    },
    makeBuildMenu: function() {
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
            cell.addEventListener('click', function() {
                console.log({
                    type: rows[i].type,
                    size: rows[i].size,
                    orientation: 'h'
                });
                self.clearUsableCells(self.pfield);
                self.colorUsableCells(self.pfield, rows[i].size, 'h');
                console.log(usableCells);
            });

            row.appendChild(cell);
            cell = document.createElement('td');
            cell.classList.add(rows[i].cssnms2[0]);
            cell.classList.add(rows[i].cssnms2[1]);

            cell.addEventListener('click', function() {
                console.log({
                    type: rows[i].type,
                    size: rows[i].size,
                    orientation: 'v'
                });
                self.clearUsableCells(self.pfield);
                self.colorUsableCells(self.pfield, rows[i].size, 'v');
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
    makeTableHeader: function(content) {
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
    getUsableCells: function(field, size, orientation) {
        let usableCells = [];
        for (let y = 0; y < 10; y++) {
            for(let x = 0; x < 10; x++) {
                let cell = field.getCell(x, y);
                if (!cell.used) {
                    if (orientation === 'h') {
                        if (x + size <= 10) {
                            usableCells.push({x,y});
                            cell.classList.add('usable');
                        }
                    } else {
                        if (y + size <= 10) {
                            usableCells.push({x, y});
                            cell.classList.add('usable');
                        }
                    }
                }
            }
        }
        return usableCells;
    },
    colorUsableCells: function(field, size, orientation) {
        let usableCells = this.getUsableCells(field, size, orientation);
        for (let i = 0; i < usableCells.length; i++) {
            let cell = field.getCell(usableCells[i].x, usableCells[i].y);
            cell.classList.add('usable');
        }
    },
    clearUsableCells: function(field) {
        let cells = field.cells;
        for (let i = 0; i < cells.length; i++) {
            let cell = cells[i];
            cell.classList.remove('usable');
        }
    },
    addShipPlacementHandler: function(field) {
        let cells = field.cells;
        for (let i = 0; i < cells.length; i++) {
            let cell = cells[i];
            let self = this;
            cell.addEventListener('click', function() {
                // calculate x and y from i
                let x = i % 10;
                let y = Math.floor(i / 10);
                self.placementHandler(x, y);
            }
            );
        }
    },
    placementHandler: function(x, y) {
        console.log('placementHandler', x, y);
    }
};