<?php

use function Core\asset;
use function Core\config;
use function Core\out;

?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <title><?= config('app.name') ?></title>
        <?= asset('css/app.css') ?>
        <script src="https://cdn.tailwindcss.com?plugins=forms"></script>
    </head>
    <body>