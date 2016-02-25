<?php

/**
 * @file
 * This is the template file for the Islandora Simple XML object.
 */
?>

<div class="islandora-simple-xml-object islandora">
  <div class="islandora-simple-xml-content-wrapper clearfix">
    <?php if (isset($islandora_content)): ?>
      <div class="islandora-simple-xml-content">
        <?php print $islandora_content; ?>
      </div>
      <?php if (isset($islandora_download_link)): ?>
        <?php print $islandora_download_link; ?>
      <?php endif; ?>
    <?php endif; ?>
  </div>
  <div class="islandora-simple-xml-metadata">
      <?php if (isset($description)): ?>
        <?php print $description; ?>
      <?php endif; ?>
    <?php if($parent_collections): ?>
      <div>
        <h2><?php print t('In collections'); ?></h2>
        <ul>
          <?php foreach ($parent_collections as $collection): ?>
            <li><?php print l($collection->label, "islandora/object/{$collection->id}"); ?></li>
          <?php endforeach; ?>
        </ul>
      </div>
    <?php endif; ?>
    <?php print $metadata; ?>
  </div>
</div>
