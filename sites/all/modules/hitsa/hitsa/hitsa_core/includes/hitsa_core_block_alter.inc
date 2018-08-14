<?php
function hitsa_core_block_list_alter(&$blocks)
{
    $field = field_info_field('field_school_selections');
    $allowed = list_allowed_values($field);
    $main_weight = 0;
    foreach ($blocks as $bl_key => &$block) {
        if ($block->delta == 'main') {
            $block->weight = 0;
            $main_weight = $block->weight;
        }
        foreach ($allowed as $delta => $val) {
            if ($block->delta == $delta) {
                $block->weight = $main_weight + 1;
            }
            $delta = str_replace('-', '_', $delta) . '_block';
            if ($delta == $block->delta) {
                if (isset($block->weight) && isset($main_weight)) {
                    $block->weight = $main_weight + 1;
                }
                $block->pages = str_replace('õ', 'o', $block->pages);
                $block->pages = str_replace('Õ', 'O', $block->pages);
                $block->pages = str_replace('ä', 'a', $block->pages);
                $block->pages = str_replace('ü', 'u', $block->pages);
                $block->pages = str_replace('Ü', 'U', $block->pages);
                $block->pages = str_replace('Ä', 'A', $block->pages);
                $block->pages = str_replace('Ö', 'O', $block->pages);
                $block->pages = str_replace('ö', 'o', $block->pages);
                $blocks[$bl_key] = $block;
                break;
            }
        }
    }
    uasort($blocks, "hitsa_sort_block_objects");
}
function hitsa_sort_block_objects($a, $b)
{
    $a_weight = (is_object($a) && isset($a->weight)) ? $a->weight : 0;
    $b_weight = (is_object($b) && isset($b->weight)) ? $b->weight : 0;
    if ($a_weight == $b_weight) {
        return 0;
    }
    return ($a_weight < $b_weight) ? -1 : 1;
}
function hitsa_core_block_info_alter(&$blocks, $theme, $code_blocks)
{
    $blocks_list = db_select('block', 'b');
    $blocks_list->fields('b');
    $blocks_list->condition('module', 'hitsa_curriculum');
    $blocks_list->condition('status', 1);
    $blocks_list->condition('pages', '', '!=');
    $results = $blocks_list->execute();
    while ($block = $results->fetchAssoc()) {
        if (!empty($block['pages']) && $block['status'] == 1) {
            $pages = $block['pages'];
            $pages = str_replace('õ', 'o', $pages);
            $pages = str_replace('Õ', 'O', $pages);
            $pages = str_replace('ä', 'a', $pages);
            $pages = str_replace('ü', 'u', $pages);
            $pages = str_replace('Ü', 'U', $pages);
            $pages = str_replace('Ä', 'A', $pages);
            $pages = str_replace('Ö', 'O', $pages);
            $pages = str_replace('ö', 'o', $pages);
            $num_updated = db_update('block') // Table name no longer needs {}
                ->fields(array(
                    'pages' => $pages,
                ))
                ->condition('bid', $block['bid'], '=')
                ->execute();
        }
    }
}