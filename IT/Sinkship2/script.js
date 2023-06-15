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
        fields.appendChild(this.cfield.field);
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
            }
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
            ship.push(cell);
            if (direction === 'h') {
                x++;
            } else {
                y++;
            }
        }
        return ship;
    },
};