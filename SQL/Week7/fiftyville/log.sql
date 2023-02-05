-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Since we don't have much pleriminary data to dig through,
-- the first thing we might want to do, is to look at the
-- crime scene' reports in hopes to glean some prefatory data.
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2021
AND street = "Humphrey Street";

-- As we can see, there's only one report we might find particalurly helpful,
-- though it should be pointed out that littering also happenned later that day,
-- as the enrty 297 indicates. But, the event hadn't been captured by anyone, so we'll
-- put it aside for now.

-- What's important, though, is that all witnesses have stated that the theft occurred at the bakery

-- So, now, we might want to look through the interviews hoping to get even more data

-- Ruth also mentions the bakery and believes to have seen the suspect getting into a car
-- 10 minutes after the incident took place. Given that, we might want to find out the car' licence
-- plate number. Eugene alleges that he saw the thief earlier this day near the ATM on Leggett Street
-- withdrawing some money. And Raymond is quite sure he saw the thief talking to somebody by phone
-- for less than a minute about him taking the earliest flight out of Fiftyville tomorrow. The thief then
-- asked the person to purchase tickets.

-- So now we might want to write a SQL query to identify the interviews that bring up incidents
-- at the "Humphrey Street bakery", that happened no earlier than 28.07.2021,
-- providing all the information we know thus far.
SELECT transcript FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28
AND transcript LIKE "%bakery%" AND "%theft%";

-- So, let's now look through our data systematically,
-- in an attempt to capitalize off of the clues we now have
SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";

-- Now, knowing the account numbers of possible criminals
-- We're able to identify who they are via their person_id
-- linked to their account numbers

-- Ultimately, the goal is to know the person's name,
-- not just their documents.
-- The number of bank account points us to the person ID, so we might just describe the following relationship
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id

-- The number of account number points us to his bank account number,
-- so once again, we need to describe the following relationship
-- narrowing the search down using the conditions known to us
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7
AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';

-- We can also introduce some already known data to find out
-- which city the thief and his accomplice(s) most likely went to
SELECT id, full_name, city FROM airports
WHERE id = 8 AND full_name = "Fiftyville Regional Airport"
AND city = "Fiftyville";

-- Now, given the interconnectness of the airports and the flights tables,
-- We may garner some additional data via queries below:
SELECT flights.id, full_name, city, flights.hour, flights.minute

-- Using the data gathered from airports table we are able to get at the possible time
-- our insolent criminals took off and where they might have gone to
-- So, first off, we need to store the value of the destination flight into a variable
-- representing the integer value of the presumed airport
FROM airports JOIN flights ON airports.id = flights.destination_airport_id

-- Then, we need to remind ourself once more where the thief had gone from
WHERE flights.origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')

-- And then we also want to narrow our search down, as well as order the results
-- so it's easier to sift through them
AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29
ORDER BY flights.hour, flights.minute;

-- First flight appears to be the one at 8:20 to LaGuardia Airport in New York City.
-- Knowing the flight, we might obtain passengers passport numbers, which in turn can prompt us with
-- the phone numbers, for both the caller and the receiver, as well as licence plate numbers we alluded to earlier
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat

-- You can figure out the suspect name by looking at his passport number
FROM people JOIN passengers ON people.passport_number = passengers.passport_number

-- Here you access the passenger passport number by using the value of the flights table
-- and then indexing into the passengers table
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29
AND flights.hour = 8 AND flights.minute = 20

-- And order the values so it's easier to examine
ORDER BY passengers.passport_number;

-- Checking the phone call records to identify the accomlplice
-- First of, examine the possible names of the caller, and put those names in the 'Suspect List'.
SELECT name, phone_calls.duration FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021 AND phone_calls.month = 7
AND phone_calls.day = 28 AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;

-- Then, examine the possible names of the call-receiver. Check if there are any peculiar patterns
SELECT name, phone_calls.duration FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021 AND phone_calls.month = 7
AND phone_calls.day = 28 AND phone_calls.duration <= 60
ORDER BY phone_calls.duration;

-- Now, Ruth said that he had seen the thief getting into a car
-- and subsequently leaving, so we might want to figure out the licence plate number.
-- We can narrow our search using some of the details Ruth laid out.
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
FROM people JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28 AND bakery_security_logs.activity = 'exit'
AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25
ORDER BY bakery_security_logs.minute;

-- Considering the analysis, we must draw the following conclusions:
-- The criminals are two gentlemen named Bruce and Robin, where the former is the abductor
-- And the latter is his accomplice. The evidence is overwhelmingly abundant and suggests
-- They are, most likely, somewhere in New York