const URL = 'http://localhost:8888/idols';

$(document)
  .on('submit', '#form', function (event) {
    event.preventDefault();

    // let data = new FormData(this);
    let data = $(this).serialize();

    axios
      .post(URL, data, {
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
        }
      })
      .then(response => console.log(response))
      .catch(error => console.log(error));
  });
