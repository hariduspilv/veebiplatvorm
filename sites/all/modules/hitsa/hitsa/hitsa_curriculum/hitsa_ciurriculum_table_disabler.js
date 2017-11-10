$('document').ready(function(){
    var element = document.querySelector('.field-name-field-subjects-table');
    var elementChildren = element.querySelectorAll('.tablefield-col-0, .tablefield-row-0');
    for (let i = 0; i < elementChildren.length; i++) {
        elementChildren[i].disabled=true;
        elementChildren[i].style.backgroundColor = "#CCCCCC";
    }
    var element = document.querySelector('.field-name-field-specialitiy-table');
    var elementChildren = element.querySelectorAll('.tablefield-row-0');
    for (let i = 0; i < elementChildren.length; i++) {
        console.dir(elementChildren[i]);
        elementChildren[i].disabled=true;
        elementChildren[i].style.backgroundColor = "#CCCCCC";
    }
    
    
    
});