<?php
/**
 * @file
 * Theming functions for the Mail Logger module.
 */

/**
 * Theme function for theme('mail_logger_read_mail').
 *
 * @ingroup themeable
 */
function theme_mail_logger_read_mail($mail) {
  $mail = $mail['mail'];
  $output = '';
  $output .= '<table class="mail-logger-wrapper">';

  $output .= '<tr class="mail-type"><td class="mail-type-label">' . t('Mail Type') . ':</td><td class="mail-type-data">' . $mail->mailkey . '</td></tr>';
  $output .= '<tr class="date-sent"><td class="date-sent-label">' . t('Date Sent') . ':</td><td class="date-sent-data">' . format_date($mail->date_sent, 'small') . '</td></tr>';
  $output .= '<tr class="mail-ipaddr"><td class="mail-ipaddr-label">' . t('User IP Address') . ':</td><td class="mail-ipaddr-data">' . check_plain($mail->ipaddr) . '</td></tr>';
  $output .= '<tr class="mail-system"><td class="mail-system-label">' . t('Mail Class') . ':</td><td class="mail-system-data">' . check_plain($mail->mail_system) . '</td></tr>';
  $output .= '<tr class="mail-from"><td class="mail-from-label">' . t('From') . ':</td><td class="mail-from-data">' . check_plain($mail->mailfrom) . '</td></tr>';
  $output .= '<tr class="mail-to"><td class="mail-to-label">' . t('To') . ':</td><td class="mail-to-data">' . check_plain($mail->mailto) . '</td></tr>';
  $output .= '<tr class="mail-subject"><td class="mail-subject-label">' . t('Subject') . ':</td><td class="mail-subject-data">' . check_plain($mail->subject) . '</td></tr>';

  $output .= '<tr class="mail-cc"><td class="mail-cc-label">CC: </td><td class="mail-cc-data">';
  $output .= (empty($mail->headers['Cc']) ? "&nbsp;" : check_plain($mail->headers['Cc']));
  $output .=  '</td></tr>';

  $output .= '<tr class="mail-bcc"><td class="mail-bcc-label">BCC: </td><td class="mail-bcc-data">';
  $output .= (empty($mail->headers['Bcc']) ? "&nbsp;" : check_plain($mail->headers['Bcc']));
  $output .=  '</td></tr>';

  $output .= '<tr class="mail-body"><td class="mail-body-label">Body: </td>';
  // Html.
  if ($mail->body != strip_tags($mail->body)) {
    if (preg_match('/<html.*?>(.*?)<\/html>/s', $mail->body, $matches)) {
      $mailbody = $matches[0];
    }
    else {
      $mailbody = $mail->body;
    }

    $mailbody = _filter_htmlcorrector($mailbody);
    $output .= '<td class="mail-body-data"><iframe srcdoc="<html>'
      . htmlspecialchars($mailbody, ENT_QUOTES)
      . '</html>" width="100%" height="500px"></iframe></td>';
  }
  // Plain text.
  else {
    $output .= '<td class="mail-body-data">' . nl2br(check_plain($mail->body)) . '</td>';
  }
  $output .= '</tr>';
  $output .= '</table>';

  return $output;
}
