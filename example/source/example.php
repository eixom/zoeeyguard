<?php

/**
 * 这是一个示例 
 */
echo '<pre>';
echo date('Y-m-d H:i:s'), PHP_EOL;
$names = get_extension_funcs('zoeeyguard');
foreach ($names as $name) {
    echo $name, PHP_EOL;
}
echo '</pre>';