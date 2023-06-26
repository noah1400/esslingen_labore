<?php 
use function Core\out;
use function Core\asset;
?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Error <? out($code); ?></title>
        <link rel="stylesheet" href="<?php asset('css/style.css') ?>">
    </head>

    <body>
        <h1>Error <? out($code); ?></h1>
        <p><? out($message); ?></p>
    </body>
</html>