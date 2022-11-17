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
        Schema::create('absences', function(Blueprint $table) {
            $table->id();
            $table->string('name'); // Name of the absence
            $table->string('description')->nullable(); // Description of the absence
            $table->boolean('is_sick')->default(false); // Is the absence sick?
            $table->boolean('is_vacation')->default(false); // Is the absence vacation?
            $table->boolean('is_travel')->default(false); // Is the absence travel?
            $table->boolean('is_flextime')->default(false); // Is the absence flextime?
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
