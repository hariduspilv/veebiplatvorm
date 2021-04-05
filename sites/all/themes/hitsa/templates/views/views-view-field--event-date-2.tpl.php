<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php
if (!empty($row->field_event_date_2)) {
  $raw = $row->field_event_date_2[0]['raw'];
  $date1  = $raw['value'];
  $date2  = $raw['value2'];
  if($date1==$date2){
    print date('d.m.Y',$date1);
  }
  else{
    print date('d.m.Y H:i',$date1).' - '.date('d.m.Y H:i',$date2);
  }
}
?>
