module.exports = function (grunt) {
	
   grunt.loadNpmTasks('grunt-includes');
   grunt.loadNpmTasks('grunt-contrib-watch');
	grunt.loadNpmTasks('grunt-contrib-concat');
	grunt.loadNpmTasks('grunt-contrib-uglify');
   grunt.loadNpmTasks('grunt-contrib-less');
   grunt.loadNpmTasks('grunt-contrib-connect');
   grunt.loadNpmTasks('grunt-webfont');
   grunt.loadNpmTasks('grunt-px-to-rem');
   grunt.loadNpmTasks('grunt-autoprefixer');
   grunt.loadNpmTasks('grunt-open');
   
   var port = 8080; //Math.floor(Math.random() * (9000 - 8000 + 1)) + 8000;
   
   grunt.initConfig({
      
      connect: {
         server: {
            options: {
               port: port
            }
         }
      },
      
      open : {
         dev: {
            path: 'http://127.0.0.1:'+port,
            app: 'Firefox'
         }
      },

      autoprefixer: {
         options:{
           browsers: ['opera >= 11', 'ff >= 3', 'chrome >= 4', 'ie >= 9'] 
         },
         default_css: {
            src: "assets/styles/default.css",
            dest: "assets/styles/default.css"
         },
      },
      
      px_to_rem: {
         dist: {
            options: {
               base: 16,
               fallback: false,
               fallback_existing_rem: false,
               ignore: [],
               map: false
            },
            files: {
               'assets/styles/default.css': ['assets/styles/default.css']
            }
         }
      },

      webfont: {
         icons: {
            src: 'dev/glyphs/*.svg',
            dest: 'assets/fonts/',
            destLess: "dev/styles/",
            options: {
               stylesheets: ['less'],
               template: "dev/glyphs/template.less",
               relativeFontPath: "../fonts/",
               fontFilename: 'iconFont',
               types: "eot,woff2,woff,ttf,svg",
               engine: "node",
               normalize: true,
               optimize: true
            }
         }
      },
      
		concat: {
         components: {
            src: [
              'dev/js/*.js'
            ],
            dest: 'assets/js/main.js'
         },
         components_dev: {
            src: [
               'dev/js/*.js',
               '!dev/js/jquery-1.10.2.min.js'
            ],
            dest: 'assets/js/main-drupal.js'
         }
      },
      
		uglify: {
         options: {
            mangle: false
         },
         js: {
            src: ['assets/js/main.js'],
            dest: 'assets/js/main.js'
         }
      },
      
      less: {
			options: {
				compress: true
			},
			development: {
				files: {
					"assets/styles/default.css": "dev/styles/build.less"
				}
			}
			
		},
      
      includes: {
         files: {
            expand: "true",
            src: ['*.html'],
            dest: '',
            cwd: 'dev/templates/',
            options: {
               silent: true
            }
         }
      },
	   
      watch: {
         html: {
            files: ["dev/templates/**/*.html"],
            tasks: ['includes']
         },
         css: {
				files: ["dev/styles/*.less"],
				tasks: ['less', 'px_to_rem', 'autoprefixer']
			},
			js: {
            files: ['dev/js/*.js'],
            tasks: ['concat', 'uglify'],
            options: {
               nospawn: true
            }
			},
         iconfont: {
				files: ["dev/glyphs/*.svg"],
				tasks: ['webfont', 'less']
			}
      }
      
   });
   
   var tasks = {
      webfont: true,
      includes: true,
      concat: true,
      uglify: true,
      less: true,
      px_to_rem: true,
      autoprefixer: true,
      connect: true,
      open: true,
      watch: true
   };
   
   var tasksArray = new Array();
   
   for( var i in tasks ){
      if( tasks[i] ){
         tasksArray.push(i);
      }   
   }
	
	var compileTasks = {
      webfont: true,
      concat: true,
      uglify: true,
      less: true,
      px_to_rem: true,
      autoprefixer: true
   };
   
   var compileArray = new Array();
   
   for( var i in compileTasks ){
      if( compileTasks[i] ){
         compileArray.push(i);
      }   
   }
   
   grunt.registerTask('default', tasksArray);
	
	grunt.registerTask('compile', compileArray);
   
};