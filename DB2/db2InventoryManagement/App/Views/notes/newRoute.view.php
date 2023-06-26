<?php

use function Core\route;
use function Core\url;
?>
<div>
    <h1>New Route</h1>
    <p>My name is <?= $name ?> and I am <?= $age ?> years old.</p>
    <p>My id is <?= $id ?>.</p>
    <p>URI: <?= url(route("newRoute", compact("id"))) ?></p>
</div>