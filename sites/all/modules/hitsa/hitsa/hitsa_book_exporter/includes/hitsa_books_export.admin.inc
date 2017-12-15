<?php
function hitsa_books_export_page(){
    $build = array();
    $form = drupal_get_form('hitsa_books_export_form');
    $build['export'] = array(
        '#markup' => drupal_render($form),
    );
    return $build;
}
function hitsa_books_export_form($form,&$form_state){
    $form = array();

    $form['nid'] = array(
        '#type' => 'textfield',
        '#name' => 'id',
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Export',
    );
    return $form;
}
function hitsa_books_export_form_submit($form, &$form_state){
   if (!empty($form_state['input']['id'])){

       $outdir = '/home/pdurbin/drupal/exported';
       $old_base_url = 'http://www.example.com';
       $limit_post_count_for_testing = 0;
       $post_limit = 20;
       $formats["4"] = 'txtl';
#$nid = 7; // About
       $nid = $form_state['input']['id']; // Internal Documentation
       $node = node_load($nid);
# handy for checking which books are visible to drush
//$books = book_get_books();
//dpm($books);
//krumo($books);
       $tree = book_menu_subtree_data($node->book);
       foreach ($tree as $books){
           $book = $books['link'];
           $loaded_book = node_load($book['nid']);
           if (!empty($books['below']))
           {
               $pages = $books['below'];
               $loaded_book->pages = hitsa_books_export_pages($pages);
           }
       }
//       dpm($node);
//       $iterated_tree =  new RecursiveArrayIterator($tree);
//       dpm($iterated_tree);
//       $it = new RecursiveIteratorIterator($iterated_tree);
//
//       $count = 0;
//       foreach ($it as $el) {
////           $depth = $it->getDepth();
////           $half = $depth / 2;
////           #print_r($el);
////           $key = $it->key();
////           $mod = $depth % 2;
////           if ($mod == 1)  {
////               continue;
////           }
////           $indent = str_repeat('-', $half);
////           if ($key != 'nid') {
////               continue;
////           }
////           $mynode = node_load($el);
////           $title = $mynode->title;
////           $title = str_replace(':', '-', $title);
////           # for... title: "Static" site
////           $title = str_replace('"', '', $title);
////           # for... title: *Expense Code Editing (for lab admins)
////           $title = str_replace('*', '', $title);
////           $body = $mynode->body;
////           $nid = $mynode->nid;
////           $format = $mynode->format;
////           $created = $mynode->created;
////           $changed = $mynode->changed;
////           $author = $mynode->name;
////           $old_url_path = $mynode->path;
////           $drupal_info = "\n----\n\nThis page was imported from Drupal, where it was known as:\n\n";
////           if ($old_url_path) {
////               $drupal_info .= "* $old_base_url/$old_url_path\n";
////           }
////           $drupal_info .= "* $old_base_url/node/$nid\n";
////           $drupal_info .= "* created: " . date("Y-m-d", $created) . "\n";
////           $drupal_info .= "* changed: " . date("Y-m-d", $changed) . " by $author\n";
////           #print "$drupal_info\n";
////           #if ($nid != 90) {
////           #if ($nid != 132) {
////           #    continue;
////           #}
////           $files = $mynode->files;
////           #print_r($files);
////           if ($files) {
////               $drupal_info .= "\nThis page had attached files (". count($files) . " of them):\n\n";
////           }
////           $filecount = 1;
////           foreach ($files as $file) {
////               #print_r($file);
////               $drupal_info .= "File $filecount:\n\n";
////               #[filepath] => sites/default/files/Proteomics_project_ProteomeDiscoverer_risks_1.xls
////               $filepath = $file->filepath;
////               $drupal_info .= "* former url: $old_base_url/$filepath\n";
////               #[filemime] => application/vnd.ms-excel
////               $filemime = $file->filemime;
////               $drupal_info .= "* type: $filemime\n";
////               #[timestamp] => 1271783235
////               $filetime = $file->timestamp;
////               $drupal_info .= "* uploaded: " . date("Y-m-d", $filetime) . "\n";
////               $drupal_info .= "* saved to: /redacted/drupal_old_internal/snapshots/2012-03-07/rc/$filepath\n";
////               $drupal_info .= "\n";
////               #[status] => 1
////               #[filename] => Proteomics_project_ProteomeDiscoverer_risks.xls
////               #[description] => Proteomics_project_ProteomeDiscoverer_risks.xls
////               $filecount++;
////           }
////           #if ($nid == 646) {
////           #    print_r($mynode);
////           #}
////           if ($limit_post_count_for_testing) {
////               #print_r($mynode);
////               if ($count > $post_limit ) {
////                   break;
////               }
////               $count++;
////           }
////           $dir;
////           $dir[$half] = $nid;
////           $path = '';
////           for ($i = 1; $i <= $half; $i++) {
////               $path .= "/$dir[$i]";
////           }
////           printf("%-23s %s ($format)\n", $path, $title);
////           #print_r($dir);
////           system("mkdir -p $outdir/$path", $retval);
////           if ($retval !== 0) {
////               print "ERROR! couldn't mkdir $outdir/$path\n";
////               break;
////           }
////           $title = preg_replace('/\r/', '', $title);
////           $body = preg_replace('/\r/', '', $body);
////           $content = "[[!meta title=\"$title\"]]\n\n$body\n$drupal_info";
////           $ext = 'mdwn';
////           if ($format == 4) {
////               $ext = $formats["4"];
////           }
////           dpm($content);
//////           $file = "$outdir/$path.$ext";
//////           print "$file\n";
//////           $fh = fopen($file, 'w') or die("can't open $file");
//////           fwrite($fh, $content);
//////           fclose($fh);
//       }
   }
}
function hitsa_books_export_pages($pages){
    $loaded_page = array();
    foreach ($pages as $page){
        $loaded_page[$page['link']['nid']] = node_load($page['link']['nid']);
        if (!empty($page['below'])){
            $loaded_page[$page['link']['nid']]->pages = hitsa_books_export_pages($page['below']);
        }

    }
    return $loaded_page;
}