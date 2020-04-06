function tileUpdate(id) {
  let num = document.getElementById(id).value;
  if (isNaN(num)) {
    alert('Input must be a number');
  }
}

function tableCreate()
{
  // create grid
  let grid = document.getElementById("gridHolder"); // get grid div
  let tbl = document.createElement('table');  // create table element
  tbl.setAttribute("id","grid")
  for(let height = 0; height < 9; height++)  // for number of rows
  {
    let tr = tbl.insertRow();   // insert table row
    for(let width = 0; width < 9; width++) // for number of columns
    {
      let td = tr.insertCell();   // insert cell in row tr
      td.style.minWidth = "40px";    // set cell dimensions
      td.style.minHeight = "40px";
  
      let btn = document.createElement("input"); // create a button element
      btn.setAttribute("class","tile");   // set class to tile
      btn.setAttribute("id","" + (width) + (height)); // set id of each button to unique identifier
      btn.setAttribute("data-x",width); // set custom attributes to describe button's x and y coordinates
      btn.setAttribute("data-y",height);// use +1 offset to create a 1 element border around the grid tiles within the tileStates array 
      btn.setAttribute("maxlength",1);
      btn.setAttribute("onChange","tileUpdate(this.id)");   // on change call function and pass button id
      td.appendChild(btn);    // insert button into table cell
    }
  }
  grid.appendChild(tbl);  // append table to div
}

// final check for invalid inputs
function finalCheck() {
  for (let h = 0; h < 9; h++) {
    for (let w = 0; w < 9; w++) {
      tileUpdate("" + w + h);
    }
  }
}

function solve() {
  finalCheck();
  var data;

}

function clearTile(id) {
  document.getElementById(id).value = "";
}

function clear() {
  for (let h = 1; h < 10; h++) {
    for (let w = 1; w < 10; w++) {
      clearTile("" + w + h);
    }
  }
}

window.onload = function()
{
  tableCreate();
  document.getElementById("solveButton").addEventListener("click", function() {solve()});
  document.getElementById("clearButton").addEventListener("click", function() {clear()});
}