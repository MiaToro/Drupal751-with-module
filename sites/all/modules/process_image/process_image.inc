<?php

/**
 * @file
 * This is to upload image and get its properties.
 *
 */
/**
 * @todo: Some additional magic things to explain:
 * - ......
 */

/**
 * 
 */
function _process_image_info() {
    return $types;
}

function _process_image_theme() {
    return array(
    );
}

/**
 * Formats child form elements as inline elements.
 * 
  function theme_process_image_inline_form_element($variables) {
  $element = $variables['element'];

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
  $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
  $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
  $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(
  ' ' => '-',
  '_' => '-',
  '[' => '-',
  ']' => '',
  )
  );
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
  $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
  $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
  case 'before':
  $output .= ' ' . theme('form_element_label', $variables);
  $output .= ' ' . '<div class="container-inline">' . $prefix . $element['#children'] . $suffix . "</div>\n";
  break;

  case 'invisible':
  case 'after':
  $output .= ' ' . $prefix . $element['#children'] . $suffix;
  $output .= ' ' . theme('form_element_label', $variables) . "\n";
  break;

  case 'none':
  case 'attribute':
  // Output no label and no required marker, only the children.
  $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
  break;
  }

  if (!empty($element['#description'])) {
  $output .= ' <div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
  }

  /**
 * Form content for examples/form_example/element_example.
 *
 * Simple form to demonstrate how to use the various new FAPI elements
 * we've defined.
 */
function process_image_demo_form($form, &$form_state) {

    // If you are familiar with how browsers handle files, you know that
    // enctype="multipart/form-data" is required. Drupal takes care of that, so
    // you don't need to include it yourself.
    $form['file'] = array(
        '#type' => 'file',
        '#title' => t('Image'),
        '#description' => t('Upload a file, allowed extensions: jpg, jpeg, png, gif'),
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
    );

    return $form;
}

/**
 * Submit handler for process_image_demo_form().
 */
function process_image_demo_form_submit($form, &$form_state) { 
    $imagefile = '';

    $file = $form_state['storage']['file'];
    // We are done with the file, remove it from storage.
    unset($form_state['storage']['file']);
    // Make the storage of the file permanent.
    $file->status = FILE_STATUS_PERMANENT;
    /*
    if ($dirh) {
        while (($dirElement = readdir($dirh)) !== false) {
            
        }
        closedir($dirh);
    } */
    // Save file status.
    $uploaded = file_save($file);
    $imagefile = drupal_realpath($file->uri); 
    /*
    $file_debug = "debug.txt";
    $debug_current = "file::: " . print_r($file, true) . PHP_EOL; 
    $debug_current .= "root::: " . print_r(drupal_realpath($file->uri), true) . PHP_EOL;      
    file_put_contents($file_debug, $debug_current, FILE_APPEND);
    */
    
    try {
        exec("CImgClient.exe " . $imagefile . " 2>&1", $output);  
    } catch (Exception $e) {
        echo "error: " . $e->getMessage(), "\n";
    }

    //
    // Set a response to the user.
    drupal_set_message(t('The image has been uploaded and saved, filename: @filename.', array('@filename' => $file->filename)));
    drupal_set_message(t('The uploaded Image\'s location: ' . drupal_realpath($file->uri)));
    drupal_set_message(t($output[0] . "px"));
    drupal_set_message(t($output[1] . "px"));
}

/**
 * Validate handler for process_image_demo_form().
 *
 * @ingroup process_image
 */
function process_image_demo_form_validate($form, &$form_state) { 

    $file = file_save_upload('file', array(
        // Validates file is really an image.
        'file_validate_is_image' => array(),
        // Validate extensions.
        'file_validate_extensions' => array('png gif jpg jpeg'),
    ));
    // If the file passed validation:
    if ($file) {
        // Move the file into the Drupal file system.
        if ($file = file_move($file, 'public://')) {
            // Save the file for use in the submit handler.
            $form_state['storage']['file'] = $file;
        } else {
            form_set_error('file', t("Failed to write the uploaded file to the site's file folder."));
        }
    } else {
        form_set_error('file', t('No file was uploaded.'));
    }
}
