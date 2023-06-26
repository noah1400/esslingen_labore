<?php 

use function Core\out;
use function Core\view;

view('partials/head');
view('partials/nav');
?>

id: <?= out($part->id) ?> <br>
name: <?= out($part->name) ?> <br>
description: <?= out($part->description) ?> <br>
category: <?= out($part->category) ?> <br>
created_at: <?= out($part->created_at) ?> <br>
updated_at: <?= out($part->updated_at) ?> <br>