<div id="user-edit-<?php print $user->uid; ?>" class="user-edit-form">
	<div class="user-edit-container" id="user-edit-container">
		<?php print render($form['form_id']); ?>
		<?php print render($form['form_build_id']); ?>
		<?php print render($form['form_token']); ?>
		<input type="input" id="ViewMode" class="currentedittab" name="ViewMode" value="" style="display: none;">
		
		<div class="usereditborder" id="usereditborder">
			<div><h3>Account Information</h3></div>
			<div><?php print render($form['account']['name']); ?></div>
			<div><?php print render($form['field_full_name']); ?></div>
			<div><?php print render($form['account']['mail']); ?></div>
			<div><hr></div>
			<div><h3>Change Password</h3></div>
			<div id="currpass" class="showalledit accountinfo changepassword toggleelement"><?php print render($form['account']['current_pass']); ?></div>
			<div class="showalledit changepassword toggleelement"><?php print render($form['account']['pass']); ?></div>

			<div><hr></div>
			<div><h3>Additional Profile Information</h3></div>
			<div><?php print render($form['timezone']['timezone']); ?><hr></div>
			<div><?php print render($form['account']['status']); ?></div>
			<div><?php print render($form['account']['roles']); ?></div>
			<div><?php print render($form['account']['notify']); ?></div>
			<div><?php print render($form['field_terms_of_use']); ?></div>
		</div>
		<?php print render($form['actions']); ?>
	</div><!--end user-edit container-->
</div><!--end user-edit-->

