-- Keep a log of any SQL queries you execute as you solve the mystery.

-- to understand database structure:
.schema
-- tables:
-- crime_scene_reports
-- interviews
-- atm_transactions
-- bank_accounts
-- airports
-- flights
-- passengers
-- phone_calls
-- people
-- bakery_security_logs

-- to look at crime scene reports. We know the duck was stolen on 28/7/2021 on Humphrey street:
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;
-- crime id is 295. took place at 10.15am. 3 interviews conducted on the day, each mentions the bakery

-- to look for interviews:
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- Ruth - thief got into a car in the parking lot - check security footage
-- Eugene - recognised thief. Saw thief withdrawing money from ATM on Leggett st in the morning
-- Raymond - as theif left bakery, they called someone for less than a minute - looking to take earliest flight out of Fiftyville tomorrow (29/7/2021). Asked other person to buy ticket

-- to look at ATM records:
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location LIKE "%Leggett%";
-- could be multiple transactions, but not a deposit transaction_type

-- look at airports:
SELECT * FROM airports;
-- Fiftyville is id 8, abbreviation CSF

-- look at earliest flight from CSF on 29/7
SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29;
-- earliest is flight id 36, leaving at 8.20
-- destination airport id = 4, which is LGA / LaGuardia Airport - New York City

-- look at bakery_security_logs
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28;

-- refine:
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10;
-- car left within 10 mins of 10.15 - multiple cars/license plates possible

-- looking for someone who's car is in that list, plus is a passenger on flight 36
-- get people IDs from flight:
SELECT people.id
FROM people, passengers
WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
    (SELECT passengers.passport_number
    FROM passengers
    WHERE passengers.flight_id = 36);

-- get people IDs from bakery_security_logs:
SELECT people.id
FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
    (SELECT bakery_security_logs.license_plate
    FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10);

-- refine to exit
SELECT people.id
FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
    (SELECT bakery_security_logs.license_plate
    FROM bakery_security_logs
    WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit");

-- select people where people id is in passenger flight list and in bakery security logs:
SELECT people.name
FROM people
WHERE people.id IN
    (SELECT people.id
    FROM people, passengers
    WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
        (SELECT passengers.passport_number
        FROM passengers
        WHERE passengers.flight_id = 36))
    AND IN
    (SELECT people.id
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit"));

-- select people where people id is in passenger flight list and in bakery security logs:
SELECT people.name
FROM people
WHERE people.id IN
    (SELECT people.id
    FROM people, passengers
    WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
        (SELECT passengers.passport_number
        FROM passengers
        WHERE passengers.flight_id = 36))
    AND
    (SELECT people.id
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit"));
-- too many names

-- check names of those on flight
SELECT people.name
FROM people, passengers
WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
    (SELECT passengers.passport_number
    FROM passengers
    WHERE passengers.flight_id = 36);

-- check nesting
SELECT people.name
FROM people
WHERE people.id IN
    ((SELECT people.id
    FROM people, passengers
    WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
        (SELECT passengers.passport_number
        FROM passengers
        WHERE passengers.flight_id = 36))
    AND
    (SELECT people.id
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit")));

-- check license plate query
SELECT people.name
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit");

-- check license plate query again
SELECT people.id
FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
    (SELECT bakery_security_logs.license_plate
    FROM bakery_security_logs
    WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit");

-- check phone calls
SELECT *
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28;

-- build nested query to check for people IDs associated with car park, flight, ATM and phone call.
-- try car park and flight first

SELECT people.id
FROM people
WHERE people.id IN
    (SELECT people.id
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit"))
    AND people.id IN
    (SELECT people.id
    FROM people, passengers
    WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
        (SELECT passengers.passport_number
        FROM passengers
        WHERE passengers.flight_id = 36));

-- people.id from ATM:
SELECT bank_accounts.person_id
FROM bank_accounts, atm_transactions
WHERE bank_accounts.account_number = atm_transactions.account_number AND bank_accounts.account_number IN
    (SELECT account_number
    FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%Leggett%");



-- add in nested for ATM
SELECT people.id
FROM people
WHERE people.id IN
    (SELECT people.id
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit"))
    AND people.id IN
    (SELECT people.id
    FROM people, passengers
    WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
        (SELECT passengers.passport_number
        FROM passengers
        WHERE passengers.flight_id = 36))
    AND people.id IN
    (SELECT bank_accounts.person_id
    FROM bank_accounts, atm_transactions
    WHERE bank_accounts.account_number = atm_transactions.account_number AND bank_accounts.account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%Leggett%"));

-- add in phone calls - check
SELECT *
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28;

-- add in phone calls - check
SELECT *
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60;

-- add in phone calls - get people ID
SELECT DISTINCT(people.id)
FROM people, phone_calls
WHERE people.phone_number = phone_calls.caller AND people.phone_number IN
    (SELECT phone_calls.caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration <=60);

-- add in nested phone calls...
SELECT people.id
FROM people
WHERE people.id IN
    (SELECT people.id
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit"))
    AND people.id IN
    (SELECT people.id
    FROM people, passengers
    WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
        (SELECT passengers.passport_number
        FROM passengers
        WHERE passengers.flight_id = 36))
    AND people.id IN
    (SELECT bank_accounts.person_id
    FROM bank_accounts, atm_transactions
    WHERE bank_accounts.account_number = atm_transactions.account_number AND bank_accounts.account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%Leggett%"))
    AND people.id IN
    (SELECT DISTINCT(people.id)
    FROM people, phone_calls
    WHERE people.phone_number = phone_calls.caller AND people.phone_number IN
        (SELECT phone_calls.caller
        FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration <=60));

-- try narrowing bakery security log time
SELECT people.id
FROM people
WHERE people.id IN
    (SELECT people.id
    FROM people, bakery_security_logs
    WHERE people.license_plate = bakery_security_logs.license_plate AND people.license_plate IN
        (SELECT bakery_security_logs.license_plate
        FROM bakery_security_logs
        WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.activity = "exit" and bakery_security_logs.minute <= 30))
    AND people.id IN
    (SELECT people.id
    FROM people, passengers
    WHERE people.passport_number = passengers.passport_number AND people.passport_number IN
        (SELECT passengers.passport_number
        FROM passengers
        WHERE passengers.flight_id = 36))
    AND people.id IN
    (SELECT bank_accounts.person_id
    FROM bank_accounts, atm_transactions
    WHERE bank_accounts.account_number = atm_transactions.account_number AND bank_accounts.account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%Leggett%"))
    AND people.id IN
    (SELECT DISTINCT(people.id)
    FROM people, phone_calls
    WHERE people.phone_number = phone_calls.caller AND people.phone_number IN
        (SELECT phone_calls.caller
        FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration <=60));

-- id is 686048
SELECT * FROM people WHERE id = 686048;

-- thief is bruce

-- who did bruce call?
SELECT *
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60 AND phone_calls.caller =
    (SELECT phone_number
    FROM people
    WHERE id = 686048);

-- get phone number
SELECT people.name
FROM people
WHERE people.phone_number =
    (SELECT receiver
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60 AND phone_calls.caller =
        (SELECT phone_number
        FROM people
        WHERE id = 686048));
