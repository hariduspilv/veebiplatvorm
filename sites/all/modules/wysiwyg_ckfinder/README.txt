Description
-----------

This module allows you to use CKFinder with the WYSIWYG version of CKEditor.
This module requires both the libraries and WYSIWYG modules. Please read the
installation instructions carefully.


Installation
------------

Read http://drupal.org/getting-started/install-contrib on how to download
and install Drupal modules.

1. Make sure that the WYSIWYG and Libraries modules are correctly installed
2. Download the CKEditor library to your libraries directory (usually
   sites/all/libraries), and create at least one WYSIWYG profile that can use 
   it.
3. Download the CKFinder library from http://ckfinder.com/download and extract 
   it to the same libaries directory.
4. Make sure that the web server has write permissions for the ckfinder 
   directory AND the file config.php
5. Make sure that you have the $cookie_domain variable set correctly in your
   settings.php file
6. Enable the 'WYSIWYG CKEditor CKFinder bridge' module
7. Edit settings via configuration link
8. Give some user roles permission to 'allow CKFinder file uploads'
9. Enable the CKFinder plugin in one of your WYSIWYG CKEditor profiles


Authors
-------

James Sinclair <james.sinclair@opc.com.au>
Carl Hinton <cbmtanzania@yahoo.co.uk>
