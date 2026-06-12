const $ = (a) => document.querySelector(a);
const $$ = (a) => document.querySelectorAll(a);

function addError(field, name){
    field.placeholder = name + " cannot be empty*";
    field.classList.add("error");
}

function removeError(field, name){
    field.placeholder = name;
    field.classList.remove("error");
}

function isEmpty(field, name){
    let empty = field.value.trim() === '';
    empty? addError(field, name) : removeError(field, name);
    return empty;
}