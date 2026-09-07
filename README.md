# Movie Ticket Booking System

A console-based movie ticket booking system built in C++, developed as part of the TCS-504 assignment.
The design follows OOP principles — encapsulation, inheritance, composition/aggregation — with a single
cinema, one screen, and multiple shows across three movies.

## Movies & Shows

| Movie              | Language | Duration | Shows (timings)          |
|---------------------|----------|----------|---------------------------|
| Mirzapur             | Hindi    | 3 hr      | e.g. 10:00 AM, 6:00 PM    |
| Avengers: Endgame    | English  | 3 hr      | e.g. 1:00 PM, 9:00 PM     |
| Super 30              | Hindi    |2.5 hr      | e.g. 4:00 PM              |

Single screen, seat layout: 10 Silver, 10 Gold, 10 Platinum seats.

## Pricing

| Seat Type | Price |
|-----------|-------|
| Silver    | ₹150  |
| Gold      | ₹250  |
| Platinum  | ₹400  |

## Project Structure

Per course rules, this project has **one class per file** and **no separate header files**.
Every class lives in its own `.cpp` file, guarded with `#ifndef`/`#define`/`#endif`, and is pulled in via
`#include` wherever it's needed. Only `main.cpp` is actually compiled directly — all other files are
included transitively through it.

MovieTicketBookingSystem/
├── SeatType.cpp
├── SeatStatus.cpp
├── BookingStatus.cpp
├── PaymentType.cpp
├── Movie.cpp
├── Seat.cpp
├── Screen.cpp
├── Cinema.cpp
├── Customer.cpp
├── Show.cpp
├── ShowSeat.cpp
├── Booking.cpp
├── Payment.cpp
├── UpiPayment.cpp
├── CardPayment.cpp
├── CashPayment.cpp
├── PriceCalculator.cpp
├── TicketPrinter.cpp
├── BookingService.cpp
├── main.cpp
└── README.md


## How to Compile & Run

Since every class file is included transitively through `main.cpp`, you only need to compile that one file:

```bash
g++ -std=c++17 main.cpp -o booking_system
./booking_system
```

On Windows (MinGW):
```bash
g++ -std=c++17 main.cpp -o booking_system.exe
booking_system.exe
```

## Features

- Browse movies and their shows
- View seat availability for a show (Silver / Gold / Platinum)
- Book one or more seats for a show
- Pay via UPI, Card, or Cash
- Automatic seat release if payment fails
- Cancel a confirmed booking (seats become available again)
- Auto-generated booking IDs (`BK1001`, `BK1002`, ...)

## Edge Cases Handled

1. Booking an already-booked seat → rejected, **no partial booking** (any-seat-fails-all-fail rule)
2. Failed payment → booking not confirmed, seats released back to available
3. Cancelling a confirmed booking → seats become available again
4. Invalid seat number or invalid menu choice → clear error message, no crash

## Design Notes

- **Encapsulation**: seat status and booking amount are private, changed only through class methods
- **No magic numbers**: seat prices come from constants in `PriceCalculator`
- **BookingService** is the sole orchestrator coordinating `Show`, `ShowSeat`, `Booking`, `Payment`, and
  `PriceCalculator` — no other class reaches across these boundaries directly
- Static counter in `Booking` generates unique booking IDs

## Class Diagram Relationships

| Pair | Type | Multiplicity |
|---|---|---|
| Cinema — Screen | Composition | 1 — 1 |
| Cinema — Show | Aggregation | 1 — 0..* |
| Screen — Seat | Composition | 1 — 1..* |
| Show — Movie | Aggregation | 1 — 1 |
| Show — Screen | Aggregation | 1 — 1 |
| Show — ShowSeat | Composition | 1 — 1..* |
| Booking — Customer | Association | 1 — 1 |
| Booking — ShowSeat | Aggregation | 1 — 1..* |
| Booking — Payment | Composition | 1 — 0..1 |
| Payment — UpiPayment/CardPayment/CashPayment | Inheritance | — |
| BookingService — Booking | Association | 1 — 0..* |
