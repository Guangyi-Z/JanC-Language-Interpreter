#include "arithmetic.h"

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

