
<table style="width:50%; margin-left:auto; margin-right:auto">
  <tr style="background-color:lightgray;">
    <td>
      Feedi link
    </td>
    <td>
      Feedi kirjeldus
    </td>
  </tr>
  <?php foreach ($feeds as $feed):?>
    <tr>
      <td>
        <a target="_blank" href="<?php print $feed['link']?>"><?php print $feed['title']?></a>
      </td>
      <td>
        <?php print $feed['desc']?>
      </td>
    </tr>
  <?php endforeach?>
</table>
