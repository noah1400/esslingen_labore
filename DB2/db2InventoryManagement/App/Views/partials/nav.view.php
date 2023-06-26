<?php

use function Core\route;
?>


<header class="bg-white">
  <nav class="mx-auto flex max-w-7xl items-center justify-between p-6 lg:px-8" aria-label="Global">
    <div class="flex items-center gap-x-12">
      <a href="#" class="-m-1.5 p-1.5">
        <span class="sr-only">Your Company</span>
        <img class="h-8 w-auto" src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=600" alt="">
      </a>
      <div class="flex gap-x-12">
        <a href="<?= route('parts.index') ?>" class="text-sm font-semibold leading-6 text-gray-900">Parts</a>
        <a href="<?= route('parts.create') ?>" class="text-sm font-semibold leading-6 text-gray-900">Add new Part</a>
        <a href="#" class="text-sm font-semibold leading-6 text-gray-900">Marketplace</a>
        <a href="#" class="text-sm font-semibold leading-6 text-gray-900">Company</a>
      </div>
    </div>
  </nav>
</header>