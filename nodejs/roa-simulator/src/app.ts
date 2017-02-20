///<reference path="../def/node.d.ts" />
///<reference path="../def/express.d.ts" />

import express = require('express');
import http = require('http');
import path = require('path');

var log4js = require("log4js");

var defaultPort = 3000;
var publicUrl = '/public';
var pubFolder = path.resolve(__dirname, '../public');

export var app = express();

app.configure(() => {
  log4js.configure({
    appenders: [
      { type: 'console' },
      {
        type: 'file',
        filename: 'access.log',
        maxLogSize: 20 * 1024 * 1024,
        backups: 10,
        category: [ 'server', 'console' ],
      },
    ],
    replaceConsole: true,
  });

  var logger = log4js.getLogger('server');
  app.use(log4js.connectLogger(logger, {
    level: log4js.levels.DEBUG,
    nolog: [ '\\.css', '\\.js', ],
    format: JSON.stringify({
      'date': ':date',
      'remote-addr': ':remote-addr',
      'method': ':method',
      'url': ':url',
      'http-version': ':http-version',
      'status': ':status',
      'content-length': ':content-length',
      'user-agent': ':user-agent',
    }),
  }));

  app.set('port', process.env.PORT || defaultPort);

  app.use(publicUrl, express.compress());
  app.use(publicUrl, express.static(pubFolder));
  app.use(publicUrl, function(req: express.Request, res: express.Response, next: Function) {
    res.send(404);
  });

  //app.use(express.bodyParser());
  //app.use(express.methodOverride());
  //app.use(express.cookieParser());
  app.use(app.router);
});

app.configure('development', () => {
  app.use(express.errorHandler({ dumpExceptions: true, showStack: true }));
});
app.configure('production', () => {
  app.use(express.errorHandler());
});

// all other routes will be handled by client-side; thus forward missing files to the index.html
app.get('/*', function(req, res) {
  // Just send the index.html for other files to support HTML5Mode
  res.sendfile('index.html', { root: pubFolder });
});

if (require.main === module) {
  var server = http.createServer(app);
  server.listen(app.get('port'), () => {
    console.log('%s server(%s) listening on port %d', process.argv[1], app.get('env'), app.get('port'));
  });
}

