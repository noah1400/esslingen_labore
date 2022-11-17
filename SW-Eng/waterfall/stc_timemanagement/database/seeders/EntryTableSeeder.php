<?php

namespace Database\Seeders;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use App\Models\WEntry;

class EntryTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        // create new WEntry
        $entry = new WEntry(
            [
                'user_id' => 1,
                'date' => '2021-01-01',
                'start_time' => '08:00:00',
                'end_time' => '16:00:00',
                'break_time' => '01:00:00',
                'hours_target' => '08:00:00',
                'hours_as_is' => '08:00:00',
                'absence_id' => null
            ]
        );
        $entry->save();
        $entry = new WEntry(
            [
                'user_id' => 2,
                'date' => '2021-01-01',
                'start_time' => '08:00:00',
                'end_time' => '16:00:00',
                'break_time' => '01:00:00',
                'hours_target' => '08:00:00',
                'hours_as_is' => '08:00:00',
                'absence_id' => null
            ]
        );
        $entry->save();
        $entry = new WEntry(
            [
                'user_id' => 3,
                'date' => '2021-01-01',
                'start_time' => '08:00:00',
                'end_time' => '16:00:00',
                'break_time' => '01:00:00',
                'hours_target' => '08:00:00',
                'hours_as_is' => '08:00:00',
                'absence_id' => null
            ]
        );
        $entry->save();
    }
}
