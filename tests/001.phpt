--TEST--
Check for zoeeyguard presence
--FILE--
<?php
echo extension_loaded("zoeeyguard");
?>
--EXPECT--
1
