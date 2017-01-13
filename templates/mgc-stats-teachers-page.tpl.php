<div class="ai-wrapper">
    <div class="ai-form-wrapper">
      <?php
      $robo_form = drupal_get_form('mgc_robo_form');
      $robo_form = drupal_render($robo_form);
      print $robo_form;
      ?>
    </div>
</div>