// 全局变量
let currentPage = 1;
let totalPages = 1;
let totalItems = 0;
let currentData = [];
let userInfo = {
  id: null,
  username: '',
  isAdmin: false
};
let selectedIds = new Set();

// 页面加载完成后初始化
document.addEventListener('DOMContentLoaded', function () {
  const token = localStorage.getItem('token');
  if (!token) {
    alert('请先登录');
    window.location.href = 'index.html';
    return;
  }

  // 初始化主题
  const savedTheme = localStorage.getItem('theme') || 'light';
  document.body.className = savedTheme + '-theme';
  updateThemeToggleText(savedTheme);

  // 验证用户会话
  validateUserSession();
});

// 验证用户会话
async function validateUserSession() {
  showLoading();
  try {
    const response = await fetch('/api/auth/me', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const result = await response.json();
      userInfo = {
        id: result.id,
        username: result.username,
        isAdmin: result.isAdmin
      };

      // 保存用户信息到本地存储
      localStorage.setItem('userInfo', JSON.stringify(userInfo));

      // 初始化页面
      initPage();
    } else {
      logout();
    }
  } catch (error) {
    console.error('验证会话失败:', error);
    logout();
  } finally {
    hideLoading();
  }
}

// 初始化页面
function initPage() {
  // 更新欢迎信息
  document.getElementById('currentUser').textContent = `欢迎，${userInfo.username}${userInfo.isAdmin ? ' (管理员)' : ''}`;

  // 更新用户信息页面
  updateUserInfo();

  // 显示管理员菜单项
  if (userInfo.isAdmin) {
    const adminItems = document.querySelectorAll('.admin-only');
    adminItems.forEach(item => {
      item.style.display = 'block';
    });
  }

  // 加载数据
  loadData();
}

// 更新用户信息页面
function updateUserInfo() {
  document.getElementById('usernameInfo').textContent = userInfo.username;
  document.getElementById('roleInfo').textContent = userInfo.isAdmin ? '管理员' : '普通用户';
  document.getElementById('lastLoginInfo').textContent = new Date().toLocaleString();
}

// 加载数据
async function loadData(page = 1) {
  showLoading();
  try {
    const searchTerm = document.getElementById('searchInput')?.value || '';
    const limit = 10; // 每页显示10条数据
    const response = await fetch(`/api/data/persons?page=${page}&limit=${limit}&search=${encodeURIComponent(searchTerm)}&order=编号:asc`, {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const result = await response.json();
      currentData = result.data;
      totalItems = result.total;
      totalPages = Math.ceil(totalItems / limit);
      currentPage = page;

      renderData();
      updatePagination();
    } else {
      const error = await response.json();
      alert('加载数据失败: ' + error.error);
    }
  } catch (error) {
    console.error('加载数据失败:', error);
    alert('加载数据失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 渲染数据到表格
function renderData() {
  const tbody = document.getElementById('dataTableBody');
  tbody.innerHTML = '';

  currentData.forEach(person => {
    const row = document.createElement('tr');
    row.dataset.id = person.id;

    // 计算年龄
    const birthDate = new Date(person['出生年月']);
    const today = new Date();
    let age = today.getFullYear() - birthDate.getFullYear();
    const monthDiff = today.getMonth() - birthDate.getMonth();
    if (monthDiff < 0 || (monthDiff === 0 && today.getDate() < birthDate.getDate())) {
      age--;
    }

    row.innerHTML = `
      <td><input type="checkbox" class="row-checkbox" data-id="${person.id}" onchange="toggleRowSelection(${person.id})"></td>
      <td>${person['编号']}</td>
      <td>${person['姓名']}</td>
      <td>${person['性别']}</td>
      <td>${person['身份证号']}</td>
      <td>${new Date(person['出生年月']).toLocaleDateString()}</td>
      <td>${person['通讯地址'] || '无'}</td>
      <td>${age}</td>
      <td>
        <button class="btn btn-primary btn-sm" onclick="editData(${person.id})">编辑</button>
        <button class="btn btn-danger btn-sm" onclick="deleteData(${person.id})">删除</button>
      </td>
    `;

    tbody.appendChild(row);
  });

  // 清除选中状态
  selectedIds.clear();
  document.getElementById('selectAll').checked = false;
}

// 更新分页信息
function updatePagination() {
  document.getElementById('pageInfo').textContent = `第 ${currentPage} 页，共 ${totalPages} 页`;
}

// 搜索数据
function searchData() {
  loadData(1);
}

// 清除搜索
function clearSearch() {
  document.getElementById('searchInput').value = '';
  loadData(1);
}

// 上一页
function previousPage() {
  if (currentPage > 1) {
    loadData(currentPage - 1);
  }
}

// 下一页
function nextPage() {
  if (currentPage < totalPages) {
    loadData(currentPage + 1);
  }
}

// 显示指定部分
function showSection(sectionId) {
  const sections = document.querySelectorAll('.section');
  sections.forEach(section => {
    section.style.display = 'none';
  });

  const targetSection = document.getElementById(sectionId);
  if (targetSection) {
    targetSection.style.display = 'block';
  }

  // 更新导航状态
  const navItems = document.querySelectorAll('.nav-item');
  navItems.forEach(item => {
    item.classList.remove('active');
  });

  // 设置当前导航项为活动状态
  const activeNavItem = document.querySelector(`.nav-item[onclick="showSection('${sectionId}')"]`);
  if (activeNavItem) {
    activeNavItem.classList.add('active');
  }


}

// 切换主题
function toggleTheme() {
  const currentTheme = document.body.classList.contains('dark-theme') ? 'dark' : 'light';
  const newTheme = currentTheme === 'light' ? 'dark' : 'light';

  document.body.className = newTheme + '-theme';
  localStorage.setItem('theme', newTheme);
  updateThemeToggleText(newTheme);
}

// 更新主题切换按钮文本
function updateThemeToggleText(theme) {
  const button = document.getElementById('themeToggle');
  if (button) {
    button.innerHTML = theme === 'light' ? '🌙 深色模式' : '☀️ 浅色模式';
  }
}

// 显示添加数据模态框
function showAddModal() {
  document.getElementById('modalTitle').textContent = '添加数据';
  document.getElementById('dataForm').reset();
  document.getElementById('dataModal').style.display = 'block';
  // 移除之前的id属性，确保是添加新数据
  delete document.getElementById('dataForm').dataset.id;
}

// 显示编辑数据模态框
async function editData(id) {
  showLoading();
  try {
    const response = await fetch(`/api/data/persons/${id}`, {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const person = await response.json();
      document.getElementById('modalTitle').textContent = '编辑数据';

      // 填充表单数据
      const form = document.getElementById('dataForm');
      form.dataset.id = id;

      // 设置表单字段值
      Object.keys(person).forEach(key => {
        const input = form.elements[key];
        if (input) {
          if (input.type === 'date') {
            input.value = new Date(person[key]).toISOString().split('T')[0];
          } else {
            input.value = person[key] || '';
          }
        }
      });

      document.getElementById('dataModal').style.display = 'block';
    } else {
      const error = await response.json();
      alert('获取数据失败: ' + error.error);
    }
  } catch (error) {
    console.error('编辑数据失败:', error);
    alert('编辑数据失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 保存数据
async function saveData(event) {
  event.preventDefault();
  showLoading();

  const form = document.getElementById('dataForm');
  const formData = new FormData(form);
  const data = {};

  // 转换FormData为普通对象
  formData.forEach((value, key) => {
    data[key] = value;
  });

  try {
    let response;
    const id = form.dataset.id;

    if (id) {
      // 更新数据
      response = await fetch(`/api/data/persons/${id}`, {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(data)
      });
    } else {
      // 添加新数据
      response = await fetch('/api/data/persons', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify(data)
      });
    }

    if (response.ok) {
      alert(id ? '数据更新成功' : '数据添加成功');
      closeModal('dataModal');
      loadData(currentPage);
    } else {
      const error = await response.json();
      alert('保存数据失败: ' + error.error);
    }
  } catch (error) {
    console.error('保存数据失败:', error);
    alert('保存数据失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 删除数据
async function deleteData(id) {
  if (confirm('确定要删除这条数据吗？')) {
    showLoading();
    try {
      const response = await fetch(`/api/data/persons/${id}`, {
        method: 'DELETE',
        headers: {
          'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
      });

      if (response.ok) {
        alert('数据删除成功');
        loadData(currentPage);
      } else {
        const error = await response.json();
        alert('删除数据失败: ' + error.error);
      }
    } catch (error) {
      console.error('删除数据失败:', error);
      alert('删除数据失败: ' + error.message);
    } finally {
      hideLoading();
    }
  }
}

// 切换全选
function toggleSelectAll() {
  const selectAllCheckbox = document.getElementById('selectAll');
  const checkboxes = document.querySelectorAll('.row-checkbox');

  checkboxes.forEach(checkbox => {
    checkbox.checked = selectAllCheckbox.checked;
    const id = parseInt(checkbox.dataset.id);
    if (selectAllCheckbox.checked) {
      selectedIds.add(id);
    } else {
      selectedIds.delete(id);
    }
  });
}

// 切换单行选择
function toggleRowSelection(id) {
  const checkbox = document.querySelector(`.row-checkbox[data-id="${id}"]`);
  if (checkbox) {
    if (checkbox.checked) {
      selectedIds.add(id);
    } else {
      selectedIds.delete(id);
    }

    // 更新全选状态
    updateSelectAllStatus();
  }
}

// 更新全选状态
function updateSelectAllStatus() {
  const selectAllCheckbox = document.getElementById('selectAll');
  const checkboxes = document.querySelectorAll('.row-checkbox');
  const allChecked = Array.from(checkboxes).every(checkbox => checkbox.checked);
  selectAllCheckbox.checked = allChecked;
}

// 删除选中数据
async function deleteSelected() {
  if (selectedIds.size === 0) {
    alert('请先选择要删除的数据');
    return;
  }

  if (confirm(`确定要删除选中的 ${selectedIds.size} 条数据吗？`)) {
    showLoading();
    try {
      const response = await fetch('/api/data/persons', {
        method: 'DELETE',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': 'Bearer ' + localStorage.getItem('token')
        },
        body: JSON.stringify({ ids: Array.from(selectedIds) })
      });

      if (response.ok) {
        alert('批量删除成功');
        loadData(currentPage);
      } else {
        const error = await response.json();
        alert('批量删除失败: ' + error.error);
      }
    } catch (error) {
      console.error('批量删除失败:', error);
      alert('批量删除失败: ' + error.message);
    } finally {
      hideLoading();
    }
  }
}

// 导入数据
function importData() {
  document.getElementById('fileInput').click();
}

// 处理文件导入
async function handleFileImport(event) {
  const file = event.target.files[0];
  if (!file) return;

  showLoading();
  try {
    const formData = new FormData();
    formData.append('file', file);

    const response = await fetch('/api/data/import', {
      method: 'POST',
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: formData
    });

    if (response.ok) {
      const result = await response.json();
      alert(`数据导入成功，共导入 ${result.count} 条记录`);
      loadData(currentPage);
    } else {
      const error = await response.json();
      alert('数据导入失败: ' + error.error);
    }
  } catch (error) {
    console.error('数据导入失败:', error);
    alert('数据导入失败: ' + error.message);
  } finally {
    hideLoading();
    // 重置文件输入
    event.target.value = '';
  }
}

// 导出数据
async function exportData() {
  showLoading();
  try {
    const response = await fetch('/api/data/export', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      responseType: 'blob'
    });

    if (response.ok) {
      const blob = await response.blob();
      const url = window.URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = `数据导出_${new Date().toISOString().slice(0, 10)}.csv`;
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    } else {
      const error = await response.json();
      alert('数据导出失败: ' + error.error);
    }
  } catch (error) {
    console.error('数据导出失败:', error);
    alert('数据导出失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 从服务器加载
async function loadFromServer() {
  showLoading();
  try {
    const response = await fetch('/api/data/load-from-server', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const result = await response.json();
      alert(result.message);
      loadData(currentPage);
    } else {
      const error = await response.json();
      alert('从服务器加载失败: ' + error.error);
    }
  } catch (error) {
    console.error('从服务器加载失败:', error);
    alert('从服务器加载失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 保存当前至服务器
async function saveToServer() {
  showLoading();
  try {
    const response = await fetch('/api/data/save-to-server', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ data: currentData })
    });

    if (response.ok) {
      const result = await response.json();
      alert(result.message);
    } else {
      const error = await response.json();
      alert('保存到服务器失败: ' + error.error);
    }
  } catch (error) {
    console.error('保存到服务器失败:', error);
    alert('保存到服务器失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// KH功能
async function khAction() {
  showLoading();
  try {
    const response = await fetch('/api/data/kh', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ data: currentData })
    });

    if (response.ok) {
      const result = await response.json();
      alert(result.message);
    } else {
      const error = await response.json();
      alert('KH功能执行失败: ' + error.error);
    }
  } catch (error) {
    console.error('KH功能执行失败:', error);
    alert('KH功能执行失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 显示修改密码模态框
function showChangePasswordModal() {
  document.getElementById('passwordForm').reset();
  document.getElementById('passwordModal').style.display = 'block';
}

// 修改密码
async function changePassword(event) {
  event.preventDefault();
  showLoading();

  const oldPassword = document.getElementById('oldPassword').value;
  const newPassword = document.getElementById('newPassword').value;
  const confirmPassword = document.getElementById('confirmPassword').value;

  if (newPassword !== confirmPassword) {
    hideLoading();
    alert('两次输入的新密码不一致');
    return;
  }

  try {
    const response = await fetch('/api/auth/change-password', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ oldPassword, newPassword })
    });

    if (response.ok) {
      alert('密码修改成功，请重新登录');
      logout();
    } else {
      const error = await response.json();
      alert('密码修改失败: ' + error.error);
    }
  } catch (error) {
    console.error('密码修改失败:', error);
    alert('密码修改失败: ' + error.message);
  } finally {
    hideLoading();
    closeModal('passwordModal');
  }
}

// 显示修改用户名模态框
function showChangeUsernameModal() {
  const username = localStorage.getItem('username');
  document.getElementById('currentUsername').value = username;
  document.getElementById('newUsername').value = '';
  document.getElementById('password').value = '';
  document.getElementById('usernameModal').style.display = 'block';
}

// 修改用户名
async function changeUsername(event) {
  event.preventDefault();
  showLoading();

  const newUsername = document.getElementById('newUsername').value;
  const password = document.getElementById('password').value;

  try {
    const response = await fetch('/api/auth/change-username', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ newUsername, password })
    });

    if (response.ok) {
      const result = await response.json();
      alert('用户名修改成功');

      // 更新本地存储和页面显示
      localStorage.setItem('username', newUsername);
      document.getElementById('usernameInfo').textContent = newUsername;
      document.getElementById('currentUser').textContent = `欢迎，${newUsername}${userInfo.isAdmin ? ' (管理员)' : ''}`;

      closeModal('usernameModal');
    } else {
      const error = await response.json();
      alert('用户名修改失败: ' + error.error);
    }
  } catch (error) {
    console.error('用户名修改失败:', error);
    alert('用户名修改失败: ' + error.message);
  } finally {
    hideLoading();
  }
}



// 显示加载指示器
function showLoading() {
  const loadingIndicator = document.getElementById('loadingIndicator');
  if (loadingIndicator) {
    loadingIndicator.style.display = 'block';
  }
}

// 隐藏加载指示器
function hideLoading() {
  const loadingIndicator = document.getElementById('loadingIndicator');
  if (loadingIndicator) {
    loadingIndicator.style.display = 'none';
  }
}

// 关闭模态框
function closeModal(modalId) {
  const modal = document.getElementById(modalId);
  if (modal) {
    modal.style.display = 'none';
  }
}

// 登出
function logout() {
  localStorage.removeItem('token');
  localStorage.removeItem('userInfo');
  localStorage.removeItem('theme');
  window.location.href = 'index.html';
}

// 显示用户管理界面
async function showUserManagement() {
  const userManagementDiv = document.getElementById('user-management');
  if (userManagementDiv.style.display === 'none') {
    userManagementDiv.style.display = 'block';
    await loadUsers();
  } else {
    userManagementDiv.style.display = 'none';
  }
}

// 加载用户列表
async function loadUsers() {
  showLoading();
  try {
    const response = await fetch('/api/admin/users', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const users = await response.json();
      renderUserList(users);
    } else {
      const error = await response.json();
      alert('获取用户列表失败: ' + error.error);
    }
  } catch (error) {
    console.error('加载用户失败:', error);
    alert('加载用户列表失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 渲染用户列表
function renderUserList(users) {
  const tbody = document.getElementById('userTableBody');
  tbody.innerHTML = '';

  users.forEach(user => {
    const row = document.createElement('tr');

    // 仅admin用户显示删除和封禁按钮
    let actionButtons = '';
    if (userInfo.username === 'admin') {
      actionButtons = `
        <td>
          <button class="btn btn-${user.isBanned ? 'success' : 'danger'} btn-sm" onclick="toggleBanUser(${user.id}, ${!user.isBanned})">
            ${user.isBanned ? '解封' : '封禁'}
          </button>
          <button class="btn btn-danger btn-sm" onclick="deleteUser(${user.id})">删除</button>
        </td>
      `;
    } else {
      actionButtons = '<td>无权限</td>';
    }

    row.innerHTML = `
      <td>${user.id}</td>
      <td>${user.username}</td>
      <td>${user.isAdmin ? '管理员' : '普通用户'}</td>
      <td>${user.isBanned ? '已封禁' : '正常'}</td>
      <td>${user.lastLogin ? new Date(user.lastLogin).toLocaleString() : '从未登录'}</td>
      <td>${new Date(user.createdAt).toLocaleString()}</td>
      ${actionButtons}
    `;
    tbody.appendChild(row);
  });
}

// 显示注册新用户模态框
function showAddUserModal() {
  document.getElementById('addUserForm').reset();
  document.getElementById('addUserModal').style.display = 'block';
}

// 注册新用户
async function addUser(event) {
  event.preventDefault();
  showLoading();

  const username = document.getElementById('newUserUsername').value;
  const password = document.getElementById('newUserPassword').value;
  const isAdmin = document.getElementById('newUserIsAdmin').value === 'true';

  try {
    const response = await fetch('/api/admin/users', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ username, password, isAdmin })
    });

    if (response.ok) {
      const result = await response.json();
      alert('用户注册成功');
      closeModal('addUserModal');
      await loadUsers(); // 重新加载用户列表
    } else {
      const error = await response.json();
      alert('用户注册失败: ' + error.error);
    }
  } catch (error) {
    console.error('注册用户失败:', error);
    alert('用户注册失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 删除用户
async function deleteUser(userId) {
  if (confirm('确定要删除该用户吗？')) {
    showLoading();
    try {
      const response = await fetch(`/api/admin/users/${userId}`, {
        method: 'DELETE',
        headers: {
          'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
      });

      if (response.ok) {
        const result = await response.json();
        alert(result.message);
        await loadUsers(); // 重新加载用户列表
      } else {
        const error = await response.json();
        alert('删除用户失败: ' + error.error);
      }
    } catch (error) {
      console.error('删除用户失败:', error);
      alert('删除用户失败: ' + error.message);
    } finally {
      hideLoading();
    }
  }
}

// 封禁/解封用户
async function toggleBanUser(userId, isBanned) {
  showLoading();
  try {
    const response = await fetch(`/api/admin/users/${userId}/ban`, {
      method: 'PUT',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ isBanned })
    });

    if (response.ok) {
      const result = await response.json();
      alert(result.message);
      await loadUsers(); // 重新加载用户列表
    } else {
      const error = await response.json();
      alert('更新用户状态失败: ' + error.error);
    }
  } catch (error) {
    console.error('更新用户状态失败:', error);
    alert('更新用户状态失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 管理用户（管理员功能）
function manageUsers() {
  showUserManagement();
}

// 加载当前注册口令
async function loadRegistrationToken() {
  showLoading();
  try {
    const response = await fetch('/api/admin/registration-token', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const result = await response.json();
      const token = result.token;
      const tokenManagementDiv = document.getElementById('registration-token-management');

      if (token) {
        document.getElementById('currentToken').value = token.token;
        document.getElementById('tokenExpiry').value = new Date(token.expiresAt).toLocaleString();
      } else {
        document.getElementById('currentToken').value = '暂无有效口令';
        document.getElementById('tokenExpiry').value = '无';
      }

      // 显示注册口令管理内容
      tokenManagementDiv.style.display = 'block';
      // 隐藏用户管理内容
      document.getElementById('user-management').style.display = 'none';
    } else {
      const error = await response.json();
      alert('获取注册口令失败: ' + error.error);
    }
  } catch (error) {
    console.error('加载注册口令失败:', error);
    alert('加载注册口令失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 生成新的注册口令
async function generateRegistrationToken() {
  if (confirm('确定要生成新的注册口令吗？这将使之前的口令失效。')) {
    showLoading();
    try {
      const response = await fetch('/api/admin/registration-token', {
        method: 'POST',
        headers: {
          'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
      });

      if (response.ok) {
        const result = await response.json();
        const token = result.token;

        document.getElementById('currentToken').value = token.token;
        document.getElementById('tokenExpiry').value = new Date(token.expiresAt).toLocaleString();

        // 显示注册口令管理内容
        document.getElementById('registration-token-management').style.display = 'block';
        // 隐藏用户管理内容
        document.getElementById('user-management').style.display = 'none';

        alert('新的注册口令已生成！');
      } else {
        const error = await response.json();
        alert('生成注册口令失败: ' + error.error);
      }
    } catch (error) {
      console.error('生成注册口令失败:', error);
      alert('生成注册口令失败: ' + error.message);
    } finally {
      hideLoading();
    }
  }
}

// 备份系统（管理员功能）
function backupSystem() {
  alert('没写');
}

// 查看日志（管理员功能）
function viewLogs() {
  alert('没写');
}

// 加载数据分析
async function loadAnalysis() {
  const analysisContent = document.getElementById('analysisContent');
  analysisContent.innerHTML = '<p>加载数据分析中...</p>';

  try {
    // 这里可以添加数据分析逻辑
    // 示例：统计数据数量和性别分布
    const total = currentData.length;
    const maleCount = currentData.filter(item => item['性别'] === '男').length;
    const femaleCount = currentData.filter(item => item['性别'] === '女').length;

    let html = `<h3>数据分析结果</h3>`;
    html += `<p>总数据量: ${total} 条</p>`;
    html += `<p>男性: ${maleCount} 人 (${((maleCount / total) * 100).toFixed(1)}%)</p>`;
    html += `<p>女性: ${femaleCount} 人 (${((femaleCount / total) * 100).toFixed(1)}%)</p>`;

    analysisContent.innerHTML = html;
  } catch (error) {
    console.error('加载数据分析失败:', error);
    analysisContent.innerHTML = '<p>加载数据分析失败</p>';
  }
}

// 点击模态框外部关闭模态框
window.onclick = function (event) {
  if (event.target.classList.contains('modal')) {
    event.target.style.display = 'none';
  }
};

// 监听键盘事件，ESC关闭模态框
document.addEventListener('keydown', function (event) {
  if (event.key === 'Escape') {
    const modals = document.querySelectorAll('.modal');
    modals.forEach(modal => {
      modal.style.display = 'none';
    });
  }
});

// 自动保存功能（可选）
let autoSaveTimer;
function startAutoSave() {
  autoSaveTimer = setInterval(() => {
    console.log('自动保存...');
    // 这里可以添加自动保存逻辑
  }, 300000); // 每5分钟自动保存一次
}

// 初始化自动保存
startAutoSave();

// 页面卸载时清除定时器
window.addEventListener('beforeunload', function () {
  if (autoSaveTimer) {
    clearInterval(autoSaveTimer);
  }
});