--TEST--
Check for encode
--SKIPIF--
<?php
if (!extension_loaded("zoeeyguard")) {
    print "skip";
}
?>
--FILE--
<?php
echo zoeey_encode('test_string_original');
?>
--EXPECT--
SC33S898v7ep29S7JROxvRaqO7D=
