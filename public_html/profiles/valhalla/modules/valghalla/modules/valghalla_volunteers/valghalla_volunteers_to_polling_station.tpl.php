<?php
/**
 * @file
 * valghalla_volunteers_to_polling_station.tpl.php
 */
?>
<?php if($posts_to_fill): ?>
<div id="volunteer-station-list">
<?php foreach($posts_to_fill as $i => $post): ?>
  <dl class="clearfix" id="volunteer-station-list-item-<?php print $i ?>">
    <dt class="label-<?php print $post['role_title'] ?>"><?php print $post['role_title'] ?></dt>
    <dd data-post="<?php print $post['role_nid'] . $post['party_tid'] . $i;?>">
      <div class="post col-xs-6"
      <?php if(!isset($existing[$i])):?> style="display:none;" <?php endif;?> >
        <?php print $existing[$i]['data']; ?>
      </div>
      <div class="col-xs-6"
      <?php if(isset($existing[$i])):?> style="display:none;" <?php endif;?> >
        <input type="text" class="form-control" placeholder="Vælg en deltager" />
      </div>
    <a data-role_nid="<?php print $post['role_nid']; ?>"
       data-party_tid="<?php print $post['party_tid']; ?>"
       data-pollingstation_nid="<?php print $pollingstation_nid; ?>"
      <?php if(isset($existing[$i])): ?> style="display:none;"  <?php endif;?> class="btn btn-default btn-xs js-add-volunteer"><span class="glyphicon glyphicon-plus"></span></a>

<?php $add_url = url('valghalla/deltagere/tilfoej', array(
  'query' => array(
    'role_nid' => $post['role_nid'],
    'party_tid' => $post['party_tid'],
    'pollingstation_nid' => $pollingstation_nid,
    'destination' => current_path(),
  ),
));
?>
    <a href="<?php print $add_url; ?>" <?php if(isset($existing[$i])): ?> style="display:none;"  <?php endif;?> class="btn btn-default btn-xs"><span class="glyphicon glyphicon-user"></span><span class="glyphicon glyphicon-plus"></span></a>

    <?php if(isset($existing[$i])): ?>
      <a href="/node/<?php print $existing[$i]['nid'] ?>/edit?destination=<?php print (implode('/', arg())) ?>" class="btn btn-default btn-xs edit"><span class="glyphicon glyphicon-user"></span></a>
      <a data-fcid="<?php print $existing[$i]['fcid'] ?>" class="remove btn btn-default btn-xs js-remove-volunteer" ><span class="glyphicon glyphicon-minus"></span></a>
    <?php endif; ?>
    </dd>
  </dl>
<?php endforeach; ?>
</div>
<?php endif; ?>
