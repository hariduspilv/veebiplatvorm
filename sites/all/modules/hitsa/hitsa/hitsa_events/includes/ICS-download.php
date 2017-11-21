
<?php

include 'ICS.php';

header('Content-type: text/calendar; charset=utf-8');
header('Content-Disposition: attachment; filename=invite.ics');

$ics = new ICS(array(
    'location' => $location->name,
    'description' => $event->title,
    'dtstart' => gmdate('U',$post['date']),
    'dtend' => gmdate('U',$post['date']),
    'summary' => $event->title,
    'url' => url('calendar')
));

return $ics;