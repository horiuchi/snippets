'use strict';

module.exports = function (grunt) {
  require('load-grunt-tasks')(grunt);
  var pkg = grunt.file.readJSON('package.json');

  grunt.initConfig({
    // config node
    dist: {
      lib: 'lib',
      client_js: 'public/js',
    },
    src: {
    },


    clean: [ dist.client_js + '/*' , dist.lib + '/*'],

    bower: {
      install: {
        options: {
          targetDir: './public/vendor',
          layout: 'byType',
        },
      },
    },

    typescript: {
      app: {
        src:  'src/app.ts',
        dest: dist.lib,
        options: {
          target: 'ES5',
          module: 'commonjs',
          base_path: 'src',
          ignoreTypeCheck: false,
          declaration: true,
        },
      },
      client: {
        src:  'src/client/**/*.ts',
        dest: dist.client_js,
        options: {
          base_path: 'src/client',
          ignoreTypeCheck: false,
          declaration: true,
        },
      },
    },

    ngmin: {
      dist: {
        src: ['<%= concat.dist.dest %>'],
        dest: '<%= concat.dist.dest %>'
      }
    },

    watch: {
      tsc_src: {
        files: [ 'src/**/*.ts', '!src/client/**/*.ts' ],
        tasks: [ 'typescript:app',],
      },
      tsc_client: {
        files: [ 'src/client/**/*.ts' ],
        tasks: [ 'typescript:client',],
      },
    },

  });

  grunt.registerTask('build', ['bower:install', 'typescript']);
  grunt.registerTask('default', ['build']);
}

