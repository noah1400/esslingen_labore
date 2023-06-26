<?php

use function Core\out;
use function Core\route;
use function Core\url;
use function Core\view;

view('partials/head');
view('partials/nav');
?>

<div class="mx-auto px-16">

    <div class="px-4 sm:px-6 lg:px-8">
        <div class="sm:flex sm:items-center">
            <div class="sm:flex-auto">
                <h1 class="text-base font-semibold leading-6 text-gray-900">Parts</h1>
                <p class="mt-2 text-sm text-gray-700">A list of all Parts registered.</p>
            </div>
        </div>
        <div class="mt-8 flow-root">
            <div class="-mx-4 -my-2 overflow-x-auto sm:-mx-6 lg:-mx-8">
                <div class="inline-block min-w-full py-2 align-middle">
                    <table class="min-w-full divide-y divide-gray-300">
                        <thead>
                            <tr>
                                <th scope="col" class="py-3.5 pl-4 pr-3 text-left text-sm font-semibold text-gray-900 sm:pl-6 lg:pl-8">ID</th>
                                <th scope="col" class="px-3 py-3.5 text-left text-sm font-semibold text-gray-900">Name</th>
                                <th scope="col" class="px-3 py-3.5 text-left text-sm font-semibold text-gray-900">Description</th>
                                <th scope="col" class="px-3 py-3.5 text-left text-sm font-semibold text-gray-900">Category</th>
                                <th scope="col" class="px-3 py-3.5 text-left text-sm font-semibold text-gray-900">Amount</th>
                                <th scope="col" class="relative py-3.5 pl-3 pr-4 sm:pr-6 lg:pr-8">
                                    <span class="sr-only">Edit</span>
                                </th>
                            </tr>
                        </thead>
                        <tbody class="divide-y divide-gray-200 bg-white">

                            <?php foreach ($parts as $part) : ?>

                                <tr>
                                    <td class="whitespace-nowrap py-4 pl-4 pr-3 text-sm font-medium text-gray-900 sm:pl-6 lg:pl-8"><?= out($part->id) ?></td>
                                    <td class="whitespace-nowrap px-3 py-4 text-sm text-gray-500">
                                        <a href="<?= route('parts.show', ["name"=>$part->name]) ?>">
                                        <?= out($part->name) ?>
                                        </a>
                                    </td>
                                    <td class="whitespace-nowrap px-3 py-4 text-sm text-gray-500"><?= out($part->description) ?></td>
                                    <td class="whitespace-nowrap px-3 py-4 text-sm text-gray-500"><?= out($part->category) ?></td>
                                    <td class="whitespace-nowrap px-3 py-4 text-sm text-gray-500"><?= out($part->amount) ?></td>
                                    <td class="relative whitespace-nowrap py-4 pl-3 pr-4 text-right text-sm font-medium sm:pr-6 lg:pr-8">
                                        <a href="<?= route('parts.edit', ["name"=>$part->name]) ?>" class="text-indigo-600 hover:text-indigo-900">Edit<span class="sr-only">, <?= out($part->name) ?></span></a>
                                    </td>
                                </tr>

                            <?php endforeach; ?>

                            <!-- More people... -->
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</div>