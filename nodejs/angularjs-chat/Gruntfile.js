'use strict';

module.exports = function (grunt) {
  var pkg = grunt.file.readJSON('package.json');

  grunt.initConfig({

    typescript: {
      app: {
        src:  'src/app.ts',
        dest: 'lib',
        options: {
          target: 'ES5',
          module: 'commonjs',
          base_path: 'src',
          disallowAsi: false,
          declaration: true,
        },
      },
      test: {
        src: [ 'test/**/*.ts' ],
        dest: 'test',
        options: {
          target: 'ES5',
          module: 'commonjs',
          base_path: 'test',
        },
      },
    },

    mochacli: {
      options: {
        require: [],
        files: 'test/**/*.js',
      },
      tap: {
        options: {
          reporter: 'tap',
        },
      },
    },

    uglify: {
      minify: {
        options: {
          sourceMap: function (fileName) {
            return fileName.replace(/\.js$/, '.map');
          },
        /*
          sourceMappingURL: function (path) {
            return  path.replace( /^public\/js\//, '').replace(/\.js$/, '.map');
          },
          sourceMapPrefix: 2 //cuts the two directory prefixes (public/js)
          */
        },
        files: [{
          expand: true,
          cwd: 'public/js/',
          src: ['**/*.js', '!*.min.js'],
          dest: 'public/js/',
          //ext: '.min.js',
          rename: function (dest, src) {
            return dest + src.replace(/\.js$/, '.min.js');
          }
        }]
      },
    },

    cssmin: {
      combine: {
        src: ['public/css/*.css', '!public/css/*min.css'],
        dest: 'public/css/all.min.css'
      }
    },

    bower: {
      install: {
        options: {
          targetDir: 'public/lib',
          layout: 'byComponent'
        },
      }
    },

    clean: {
      build: {
        src: [
          'public/js/*.min.js',
          'public/js/*.min.map',
          '<%= cssmin.combine.dest %>',
          '<%= bower.install.options.targetDir %>',
          'lib/**/*.js',
          'lib/**/*.d.ts',
          'lib-cov/**/*',
          'test/**/*.js',
          'coverage.html',
          'TestResult.xml',
        ],
      },
    },

    watch: {
      tsc_src: {
        files: [ '**/*.ts', '!**/*.d.ts', '!test/**/*.ts' ],
        tasks: [ 'typescript:app', 'mochacli' ],
      },
      tsc_test: {
        files: [ 'test/**/*.ts', '!**/*.d.ts' ],
        tasks: [ 'typescript:test' ],
      },
      test: {
        files: [ 'test/**/*.js' ],
        tasks: [ 'mochacli' ],
      },
      js_src: {
        files: ['public/js/**/*.js', '!**/*.min.js'],
        tasks: ['uglify'],
      },
      css_src: {
        files: ['public/**/*.css', '!**/*min.css'],
        tasks: ['cssmin'],
      },
    },

  });

  // Auto load grunt pulugin.
  for (var taskName in pkg.devDependencies) {
    if (taskName.substring(0, 6) === 'grunt-') {
      grunt.loadNpmTasks(taskName);
    }
  }


  var mochaRun = function(reporter, output, cb) {
    var mocha = grunt.util.spawn({
      cmd: "mocha",
      args: ["-R", reporter],
    }, function(err, result, code) {
      grunt.verbose.write("mochaRun result code=#{code}.");
      grunt.file.write(output, result.stdout);
      cb();
    });
  };

  // create jscoverage task
  grunt.registerTask("jscoverage", "Run jscoverage", function() { 
    var done = this.async();
    grunt.verbose.write("do jscoverage lib to lib-cov.");
    var jsc = grunt.util.spawn({
      cmd: "jscoverage",
      args: ["--no-highlight", "lib", "lib-cov"],
      opts: {
        stdio: 'inherit',
      },
    }, done);
  });

  grunt.registerTask("mocha-html-cov", "Run unittest and output html coverage", function() {
    process.env.TEST_COV = 1;
    var done = this.async();
    mochaRun("html-cov", "./coverage.html", done);
  });

  grunt.registerTask("mocha-cobertura", "Run unittest and output cobertura report", function() {
    process.env.TEST_COV = 1;
    var done = this.async();
    mochaRun("mocha-cobertura-reporter", "./TestResult.xml", done);
  });

  grunt.registerTask('test-coverage', ['typescript', 'jscoverage', 'mocha-html-cov']);
  grunt.registerTask('run', ['typescript', 'uglify', 'cssmin']);
  grunt.registerTask('default', ['run']);
};
