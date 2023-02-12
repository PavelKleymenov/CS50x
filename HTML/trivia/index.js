// Fire when the initial HTML document has been completely loaded and parsed
document.addEventListener('DOMContentLoaded', function() {

    // Query for a single HTML element
    let correct = document.querySelector('.correct');

    // Set up a click function that will be called whenever users click on the right button
    correct.addEventListener('click', function(event) {

        // Make sure the answer box turns green if the right answer is given
        correct.style.backgroundColor = 'green';

        // Alert user with a confirmatory message
        document.querySelector('#feedback1').innerHTML = 'Correct!';
        });

    // Query for multiple HTML elements that match a query
    let incorrects = document.querySelectorAll('.incorrect');

    // Make sure the function returns an array of all matching elements
    for(let i = 0; i < incorrects.length; i++)
    {
        incorrects[i].addEventListener('click', function(event) {

        // Make sure the answer box turns red if the wrong answer is given
        incorrects[i].style.backgroundColor = 'red';

         // Prompt users with 'Please try again' message
        document.querySelector('#feedback1').innerHTML = 'Incorrect';
        });
    }

    // Ensure the user has given the right answer to an input-like question
    document.querySelector('#check').addEventListener('click', function(){
       let input = document.querySelector('input');

       /* Provided you entered what follows, make sure the answer box turns green
                    and give the confirmatory feedback*/
       if(input.value == 'Sugar And Formaldehyde'){
           input.style.backgroundColor = 'green';
           document.querySelector('#feedback2').innerHTML = 'Correct!';

       }

       /* If the answer isn't what it supposed to be,
            let the user know he has to try again*/

       else {
           input.style.backgroundColor = 'red';
           document.querySelector('#feedback2').innerHTML = 'Incorrect';
       }
    });

});