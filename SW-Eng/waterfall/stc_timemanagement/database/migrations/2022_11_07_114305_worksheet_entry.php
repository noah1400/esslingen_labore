<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('worksheets_entries', function(Blueprint $table) {
            $table->id();
            $table->foreignId('user_id')->constrained('users'); // User to which the entry belongs
            $table->date('date'); // Date of the entry
            $table->time('start_time')->nullable(); // Start time of the entry
            $table->time('end_time')->nullable(); // End time of the entry
            $table->time('break_time')->nullable(); // Break time of the entry
            $table->time('hours_target')->nullable(); // Target hours of the entry
            $table->time('hours_as_is')->nullable(); // As-is hours of the entry
            $table->foreignId('absence_id')->nullable()->constrained('absences'); // Absence of the entry
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        //
    }
};
