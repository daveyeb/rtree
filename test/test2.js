var code = "me";

var flag = 1;

var test =  "' + "
  + ('!' == flag ? '' : 'escape')
  + "((interp = " + code
  + ") == null ? '' : interp) + '";

console.log(test);