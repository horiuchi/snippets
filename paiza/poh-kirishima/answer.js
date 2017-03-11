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
  var m = lines[0];
  var n = lines[1];
  var data = [];
  for (var i = 0; i < n; i++) {
    var line = lines[i + 2].replace(/(^\s+)|(\s+$)/g, "").split(" ");
    data.push({
      q: Number(line[0]),
      r: Number(line[1])
    });
  }

  var r = solve(m, data);
  console.log(r);
}

function solve(m, data) {
  data.sort(function(a, b) {
    return a.q - b.q;
  });
  var r = [{
    q: 0,
    r: 0,
    d: data.concat(),
  }];

  var result = Number.MAX_VALUE;
  while (r.length > 0) {
    var next = [];
    r.forEach(function(row) {
      for (var i = 0, len = row.d.length; i < len; ++i) {
        var data = row.d.concat();
        var d = data.splice(i, 1)[0];
        var res = {
          q: row.q + d.q,
          r: row.r + d.r,
          d: data
        };
        if (res.q >= m) {
          result = Math.min(result, res.r);
        } else if (res.d.length > 0 && res.r < result) {
          next.push(res);
        }
      }
    });
    r = next;
  }
  return result;
}

