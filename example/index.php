<?php

/**
 * 这是一个示例加密脚本，实际使用时可由项目情况自行编写 
 */
set_time_limit(0);

define('DIR_ROOT', dirname(__FILE__));
/**
 * 源码文件夹
 */
$source_dir = DIR_ROOT . '/source';
/**
 * 目标文件夹 
 */
$target_dir = DIR_ROOT . '/encoded';

/**
 *  判断文件是否需要加密
 *  需要加密的文件会被复制
 * 
 * @param string $path 文件路径
 * @return boolean  是否需要加密
 */
function is_encode($path) {
    $name = basename($path);
    $ext = pathinfo($path, PATHINFO_EXTENSION);

    if (in_array($ext, array('php', 'phpt', 'php4', 'php5'))) {
        return true;
    }

    if (in_array($name, array('config.inc'))) {
        return true;
    }

    return false;
}

/**
 * 判断文件是否需要复制
 * @param string $path 文件路径
 * @return boolean 是否需要复制
 */
function is_copy($path) {
    $name = basename($path);
    $ext = pathinfo($path, PATHINFO_EXTENSION);

    if (in_array($name, array('Thumbs.db'))) {
        return false;
    }

    if (in_array($ext, array('tmp'))) {
        return false;
    }

    return true;
}

/**
 * 输出到模板
 * @param string $code 加密后的密文
 * @return string 最终输出代码 
 */
function output($code) {
    $date = date('Y-m-d H:i:s');
    return sprintf('<?php
/* %s */
zoeey_run(\'%s\');
?>', $date, $code);
}

/* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
/*  以上为定制信息 */
/* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

$source_dir = filter_path($source_dir);
$target_dir = filter_path($target_dir);

if (!extension_loaded("zoeeyguard")) {
    print "zoeeyguard 尚未安装。";
    exit();
}

/**
 *
 * @param type $path
 * @return type 
 */
function filter_path($path) {
    return preg_replace(array('/([\\\\\/]+)/', '/\/$/'), array('/', ''), $path);
}

/**
 *
 * @param string $path_left
 * @param string $path_right
 * @return boolean 
 */
function is_related($path_left, $path_right) {
    if (strpos($path_left, $path_right) !== FALSE
            || strpos($path_right, $path_left) !== FALSE) {
        return true;
    }
    return false;
}

/**
 * PHP必须使用 ?> 结尾
 * 
 * @param string $code
 * @return string 
 */
function enclose($code) {
    do {
        $tokens = token_get_all($code);
        if (!$tokens) {
            break;
        }
        $enclose = false;
        $last_token = end($tokens);

        if ($last_token == ';') {
            $enclose = true;
            break;
        }

        if (is_array($last_token)) {
            if ($last_token[0] != T_INLINE_HTML && $last_token[0] != T_CLOSE_TAG) {
                $enclose = true;
            }
        }
    } while (0);
    if ($enclose) {
        $code .= '?>';
    }
    return $code;
}

/**
 * PHP必须使用 ?> 结尾
 * 
 * @param string $code
 * @return string 
 */
function make_dir($dir) {

    /**
     * echo $dir, ' | ', file_exists($dir), PHP_EOL;
     */
    if (!file_exists($dir)) {
        mkdir($dir, 0777, true);
        chmod($dir, 0777);
    }
}

if (is_related($source_dir, $target_dir)) {
    echo '源文件夹和目标文件夹不可为从属关系！';
    exit();
}

$source_list = array($source_dir);
$dir = null;
$encode_count = 0;
$copy_count = 0;

clearstatcache();
while (count($source_list) > 0) {
    $dir = array_pop($source_list);
    $files = glob($dir . '/*');

    foreach ($files as $file) {
        $file = filter_path($file);
        if (is_file($file)) {
            $target_path = str_replace($source_dir, $target_dir, $file);
            $target_dir = dirname($target_path);

            make_dir($target_dir);

            if (is_encode($file)) {
                $code = php_strip_whitespace($file);
                $code = enclose($code);
                $code = zoeey_encode($code);
                $code = output($code);
                file_put_contents($target_path, $code);
                $encode_count++;
            } else {
                if (is_copy($file)) {
                    copy($file, $target_path);
                    $copy_count++;
                }
            }
        } else {
            if (is_copy($file)) {

                $dir = str_replace($source_dir, $target_dir, $file);
                make_dir($dir);
            }

            $source_list[] = $file;
        }
    }
}
printf('成功加密 %d 个文件，复制 %d 个文件。', $encode_count, $copy_count)
?>

