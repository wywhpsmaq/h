const apiSearch = document.getElementById('apiSearch');

if (apiSearch) {
  apiSearch.addEventListener('input', (event) => {
    const value = event.target.value.trim().toLowerCase();
    const rows = document.querySelectorAll('tbody tr');

    rows.forEach((row) => {
      const text = row.textContent.toLowerCase();
      row.style.display = text.includes(value) ? '' : 'none';
    });
  });
}

