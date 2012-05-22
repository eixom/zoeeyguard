--TEST--
Check for decode
--SKIPIF--
<?php
if (!extension_loaded("zoeeyguard")) {
    print "skip";
}
?>
--FILE--
<?php
$code = zoeey_encode("test_string_original");
zoeey_run($code);
?>
--EXPECT--
test_string_original
