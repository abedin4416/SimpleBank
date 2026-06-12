const userInput = $("#user-id-input");
const passwordInput = $("#password-input");

function requestSubmit(){
    const userEmpty = isEmpty(userInput, "User ID");
    const passEmpty = isEmpty(passwordInput, "Password");
    if(!userEmpty && !passEmpty) $("#login-content").requestSubmit();
}

userInput.addEventListener('keydown', (event) => {
    if(event.key === 'Enter') {
        event.preventDefault();
        if(!isEmpty(userInput, "User ID")){
            passwordInput.focus();
        }
    }
});

passwordInput.addEventListener('keydown', (event) => {
    if(event.key === 'Enter'){
        event.preventDefault();
        requestSubmit();
    }
})

$("#login-submit").addEventListener('click', (event) => {
    event.preventDefault();
    requestSubmit();
})