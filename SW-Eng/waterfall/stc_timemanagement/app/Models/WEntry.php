<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\Relations\BelongsTo;

class WEntry extends Model
{
    use HasFactory;
    public $table = 'worksheets_entries';

    /**
     * Returns the user to which the entry belongs
     * @return \Illuminate\Database\Eloquent\Relations\BelongsTo
     */
    public function user() : BelongsTo
    {
        return $this->belongsTo(User::class);
    }

    /**
     * Returns the absence of the entry
     * @return \Illuminate\Database\Eloquent\Relations\BelongsTo
     */
    public function absence() : BelongsTo | null {
        return $this->belongsTo(Absence::class);
    }
}
