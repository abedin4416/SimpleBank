const $ = (a) => document.querySelector(a);
const $$ = (a) => document.querySelectorAll(a);

function addError(field){
    field.placeholder = field.dataset.ph + " cannot be empty*";
    field.classList.add("error");
}

function removeError(field){
    field.placeholder = field.dataset.ph;
    field.classList.remove("error");
}

function isEmpty(field){
    let empty = field.value.trim() === '';
    empty? addError(field) : removeError(field);
    return empty;
}

const firstInput = $(".first");
const secondInput = $(".second");

function requestSubmit(){
    const firstEmpty = isEmpty(firstInput);
    const secondEmpty = isEmpty(secondInput);
    if(!firstEmpty && !secondEmpty) $("#form-content").requestSubmit();
}

firstInput.addEventListener('keydown', (event) => {
    if(event.key === 'Enter') {
        event.preventDefault();
        if(!isEmpty(firstInput)){
            secondInput.focus();
        }
    }
});

secondInput.addEventListener('keydown', (event) => {
    if(event.key === 'Enter'){
        event.preventDefault();
        requestSubmit();
    }
})


$("#submit").addEventListener('click', (event) => {
    event.preventDefault();
    requestSubmit();
})