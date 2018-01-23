<?php
/**
 * Import page
 */
function hitsa_color_page(){
	return drupal_get_form('hitsa_color_change_form');

}

/**
 * Form for color change
 */
function hitsa_color_change_form($form, &$form_state){
	$my_color = file_get_contents('sites/all/themes/hitsa/static/dev/styles/site-theme.less');
	$form_state['storage']['file_content'] = $my_color; 
	$file_content = explode(';',$my_color);

		foreach($file_content as $site_theme_row){
			if(empty($site_theme_row)){
				continue;
			}
			$row_value = explode(':',$site_theme_row);
			$form_state['storage']['classes'][]=$row_value[0];
    $form[$row_value[0]] = array(
        '#title'=> $row_value[0] . ':',
		'#type' => 'textfield',
		'#size' => 10,
		'#default_value' => $row_value[1],
	);


			
}
$form['submit'] = array(
	'#submit' => array('hitsa_color_change'),
	'#type' => 'submit',
	'#value' => t('Vaheta värvi')
);
	return $form;
    
	
}

/**
*Save file
*/
function hitsa_color_change($form, &$form_state){
	//dpm($form_state['input']);
	//dpm($form_state['storage']['classes']);
	$output = '';
	$cmd = '';
	foreach($form_state['storage']['classes'] as $class){
		//dpm($class);
		if(!empty($form_state['values'][$class])){
			$output .= $class . ':' . $form_state['values'][$class] . ';';
			//dpm($form_state['values']);
		}
	}
	
	//exec($_SERVER['DOCUMENT_ROOT'].'/sites/all/themes/hitsa/static/Gruntfile.js');
	//putenv('PATH=' . getenv('PATH') . '/home/ubuntu/nodejs /home/ubuntu/workspace/sites/all/themes/hitsa/static/Gruntfile.js');
	//exec(' cd /sites/all/themes/hitsa/static && grunt 2>&1');
	//exec('C:\Program Files (x86)\Ampps\www\hitsa\sites\all\themes\hitsa\static\Gruntfile.js');
	//exec('cd sites/all/themes/hitsa/static/Gruntfile.js');
	//var_dump(shell_exec('cd C:\"Program Files (x86)"/Ampps/www/hitsa/sites/all/themes/hitsa/static/ && C:/Program Files/nodejs C:/Program Files/nodejs/grunt 2>&1 /dev/null'));
	//$cmd .= 'cd..';
	//$cmd .= 'cd..';
	//$cmd .= 'cd C:\Program Files (x86)"/Ampps/www/hitsa/sites/all/themes/hitsa/static ';
	//$cmd .= 'grunt watch';
	//var_dump(shell_exec($cmd));
	
	$file =fopen('sites/all/themes/hitsa/static/dev/styles/site-theme.less', 'w');
	fwrite($file, $output);
	fclose($file);
	var_dump(shell_exec('cd '.$_SERVER['DOCUMENT_ROOT'].'/sites/all/themes/hitsa/static && grunt 2>&1'));
	//$file = file_save_data($output, 'private://'. 'site-theme.less',FILE_EXISTS_REPLACE);
 return $file;
}