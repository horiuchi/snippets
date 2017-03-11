"use strict";

process.stdin.resume();
process.stdin.setEncoding('utf8');

var input = '';
process.stdin.on('data', function(chunk) {
    input += chunk;
});
process.stdin.on('end', function(){
    main(input)
});

function main(input) {
  var lines = input.split('\n');
  var b = lines[0];
  var solver = new Solver(b);
  var n = lines[1];
  var data = [];
  for (var i = 0; i < n; i++) {
    var a = lines[i + 2];
    console.log(solver.answer(a));
  }
}

function Solver(b) {
  this.b = b;
  this.b2 = b.slice(2);
  this.b3 = b.slice(3);
  // this.table = this.createTable(b);
}
Solver.prototype.createTable = function(b) {
  var table = {};
  table[b] = 'first';
  table[b - 1] = 'adjacent';
  table[b + 1] = 'adjacent';
};
Solver.prototype.answer = function(a) {
  if (this.b === a) {
    return 'first';
  } else if (this.b == (Number(a) + 1) || this.b == (a - 1)) {
    return 'adjacent';
  } else if (this.b2 == a.slice(2)) {
    return 'second';
  } else if (this.b3 == a.slice(3)) {
    return 'third';
  } else {
    return 'blank';
  }
};


