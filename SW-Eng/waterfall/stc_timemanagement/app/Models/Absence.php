<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Relations\HasOne;

class Absence extends Model
{
    use HasFactory;
    public $table = 'absences';

    /**
     * Returns the entries of the absence
     * @return \Illuminate\Database\Eloquent\Relations\HasOne
     */
    public function entry() : HasOne
    {
        return $this->hasOne(WEntry::class);
    }
}
