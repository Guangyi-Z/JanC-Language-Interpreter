#include "constant.h"

/*************************
 * Int
 */

Arithmetic* Int::AddInt(Int* o2) { return new Int(this->GetInt() + o2->GetInt());}
Arithmetic* Int::SubInt(Int* o2) { return new Int(this->GetInt() - o2->GetInt());}
Arithmetic* Int::MulInt(Int* o2) { return new Int(this->GetInt() * o2->GetInt());}
Arithmetic* Int::DivInt(Int* o2) { return new Int(this->GetInt() / o2->GetInt());}

Arithmetic* Int::AddDouble(Double* o2) { return new Double(this->GetInt() + o2->GetDouble());}
Arithmetic* Int::SubDouble(Double* o2) { return new Double(this->GetInt() - o2->GetDouble());}
Arithmetic* Int::MulDouble(Double* o2) { return new Double(this->GetInt() * o2->GetDouble());}
Arithmetic* Int::DivDouble(Double* o2) { return new Double(this->GetInt() / o2->GetDouble());}

Bool* Int::GTInt   ( Int* o2 ) { return new Bool ( this->GetInt ( ) >  o2 ->GetInt( ));}
Bool* Int::GTEQInt ( Int* o2 ) { return new Bool ( this->GetInt ( ) >= o2 ->GetInt( ));}
Bool* Int::LTInt   ( Int* o2 ) { return new Bool ( this->GetInt ( ) <  o2 ->GetInt( ));}
Bool* Int::LTEQInt ( Int* o2 ) { return new Bool ( this->GetInt ( ) <= o2 ->GetInt( ));}
Bool* Int::EQInt   ( Int* o2 ) { return new Bool ( this->GetInt ( ) == o2 ->GetInt( ));}
Bool* Int::NEQInt  ( Int* o2 ) { return new Bool ( this->GetInt ( ) != o2 ->GetInt( ));}

Bool* Int::GTDouble   ( Double* o2 ) { return new Bool ( this->GetInt ( ) >  o2 ->GetDouble( ));}
Bool* Int::GTEQDouble ( Double* o2 ) { return new Bool ( this->GetInt ( ) >= o2 ->GetDouble( ));}
Bool* Int::LTDouble   ( Double* o2 ) { return new Bool ( this->GetInt ( ) <  o2 ->GetDouble( ));}
Bool* Int::LTEQDouble ( Double* o2 ) { return new Bool ( this->GetInt ( ) <= o2 ->GetDouble( ));}
Bool* Int::EQDouble   ( Double* o2 ) { return new Bool ( this->GetInt ( ) == o2 ->GetDouble( ));}
Bool* Int::NEQDouble  ( Double* o2 ) { return new Bool ( this->GetInt ( ) != o2 ->GetDouble( ));}

/*************************
 * Double
 */

Arithmetic* Double::AddInt(Int* o2) { return new Double(this->GetDouble() + o2->GetInt());}
Arithmetic* Double::SubInt(Int* o2) { return new Double(this->GetDouble() - o2->GetInt());}
Arithmetic* Double::MulInt(Int* o2) { return new Double(this->GetDouble() * o2->GetInt());}
Arithmetic* Double::DivInt(Int* o2) { return new Double(this->GetDouble() / o2->GetInt());}

Arithmetic* Double::AddDouble(Double* o2) { return new Double(this->GetDouble() + o2->GetDouble());}
Arithmetic* Double::SubDouble(Double* o2) { return new Double(this->GetDouble() - o2->GetDouble());}
Arithmetic* Double::MulDouble(Double* o2) { return new Double(this->GetDouble() * o2->GetDouble());}
Arithmetic* Double::DivDouble(Double* o2) { return new Double(this->GetDouble() / o2->GetDouble());}

Bool* Double::GTInt   ( Int* o2 ) { return new Bool ( this->GetDouble ( ) >  o2 ->GetInt( ));}
Bool* Double::GTEQInt ( Int* o2 ) { return new Bool ( this->GetDouble ( ) >= o2 ->GetInt( ));}
Bool* Double::LTInt   ( Int* o2 ) { return new Bool ( this->GetDouble ( ) <  o2 ->GetInt( ));}
Bool* Double::LTEQInt ( Int* o2 ) { return new Bool ( this->GetDouble ( ) <= o2 ->GetInt( ));}
Bool* Double::EQInt   ( Int* o2 ) { return new Bool ( this->GetDouble ( ) == o2 ->GetInt( ));}
Bool* Double::NEQInt  ( Int* o2 ) { return new Bool ( this->GetDouble ( ) != o2 ->GetInt( ));}

Bool* Double::GTDouble   ( Double* o2 ) { return new Bool ( this->GetDouble ( ) >  o2 ->GetDouble( ));}
Bool* Double::GTEQDouble ( Double* o2 ) { return new Bool ( this->GetDouble ( ) >= o2 ->GetDouble( ));}
Bool* Double::LTDouble   ( Double* o2 ) { return new Bool ( this->GetDouble ( ) <  o2 ->GetDouble( ));}
Bool* Double::LTEQDouble ( Double* o2 ) { return new Bool ( this->GetDouble ( ) <= o2 ->GetDouble( ));}
Bool* Double::EQDouble   ( Double* o2 ) { return new Bool ( this->GetDouble ( ) == o2 ->GetDouble( ));}
Bool* Double::NEQDouble  ( Double* o2 ) { return new Bool ( this->GetDouble ( ) != o2 ->GetDouble( ));}

