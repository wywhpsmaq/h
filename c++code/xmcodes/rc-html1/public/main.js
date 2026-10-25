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
let fullAnalysisData = [];
let userPermissions = {};

function getStoredToken() {
  const localToken = localStorage.getItem('token');
  if (localToken) return localToken;

  const cookieToken = document.cookie
    .split('; ')
    .find(row => row.startsWith('token='));

  return cookieToken ? decodeURIComponent(cookieToken.split('=').slice(1).join('=')) : '';
}

function clearSessionAndRedirect() {
  localStorage.removeItem('token');
  localStorage.removeItem('userInfo');
  localStorage.removeItem('userPermissions');
  localStorage.removeItem('username');
  localStorage.removeItem('isLoggedIn');
  localStorage.removeItem('userRole');
  document.cookie = 'token=; Max-Age=0; path=/';
  window.location.href = 'index.html';
}

function showLoading() {
  const loadingIndicator = document.getElementById('loadingIndicator');
  if (loadingIndicator) {
    loadingIndicator.style.display = 'block';
  }
}

function hideLoading() {
  const loadingIndicator = document.getElementById('loadingIndicator');
  if (loadingIndicator) {
    loadingIndicator.style.display = 'none';
  }
}

function logout() {
  clearSessionAndRedirect();
}

function hasAdminPanelAccess() {
  return Boolean(
    userInfo.isAdmin ||
    (userPermissions && userPermissions.enterAdmin && userPermissions.enterAdmin.enabled)
  );
}

function applyPermissionVisibility() {
  const adminItems = document.querySelectorAll('.admin-only');
  adminItems.forEach(item => {
    item.style.display = hasAdminPanelAccess() ? 'block' : 'none';
  });

  const userSelect = document.getElementById('permissionUserSelect');
  if (userSelect && !userInfo.isAdmin) {
    userSelect.innerHTML = '<option value="">请选择用户</option>';
  }
}

// 页面加载完成后初始化
document.addEventListener('DOMContentLoaded', function () {
  const token = getStoredToken();
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
    const token = getStoredToken();
    if (!token) {
      clearSessionAndRedirect();
      return;
    }

    const response = await fetch('/api/auth/me', {
      headers: {
        'Authorization': 'Bearer ' + token
      }
    });

    if (response.ok) {
      const result = await response.json();
      userInfo = {
        id: result.id,
        username: result.username,
        isAdmin: result.isAdmin
      };
      userPermissions = result.permissions || {};

      localStorage.setItem('userInfo', JSON.stringify(userInfo));
      localStorage.setItem('userPermissions', JSON.stringify(userPermissions));
      localStorage.setItem('username', result.username);
      localStorage.setItem('isLoggedIn', 'true');
      localStorage.setItem('userRole', result.isAdmin ? 'admin' : 'user');

      applyPermissionVisibility();
      initPage();
      return;
    }

    if (response.status === 401 || response.status === 403) {
      clearSessionAndRedirect();
      return;
    }

    alert('会话验证失败，请重试');
  } catch (error) {
    console.error('验证会话失败:', error);
    if (!getStoredToken()) {
      clearSessionAndRedirect();
      return;
    }
    console.warn('服务器临时不可用，保留当前页面');
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
  if (hasAdminPanelAccess()) {
    const adminItems = document.querySelectorAll('.admin-only');
    adminItems.forEach(item => {
      item.style.display = 'block';
    });
    loadPermissionUserOptions();
    bindPermissionEvents();
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

// 一页
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

// 显指定部分
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

// 切换���题
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

// 显添加数据模态框
function showAddModal() {
  document.getElementById('modalTitle').textContent = '添加数据';
  document.getElementById('dataForm').reset();
  document.getElementById('dataModal').style.display = 'block';
  // 移除之前的id属性，确保是添加新数据
  delete document.getElementById('dataForm').dataset.id;
}

// 显编辑数据模态框
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
  const canChangePassword = userInfo.isAdmin || (userPermissions.changeInfo && userPermissions.changeInfo.changePassword);

  if (!canChangePassword) {
    alert('没有修改密码权限');
    return;
  }

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
  const canChangeUsername = userInfo.isAdmin || (userPermissions.changeInfo && userPermissions.changeInfo.changeUsername);

  if (!canChangeUsername) {
    alert('没有修改用户名权限');
    return;
  }

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

      // 更新本地存储和页���显示
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

// 封禁/解封用户
async function toggleBanUser(userId, isBanned) {
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
      alert(isBanned ? '用户已封禁' : '用户已解封');
      await loadUsers();
    } else {
      const error = await response.json();
      alert('更新用户状态失败: ' + (error.error || '未知错误'));
    }
  } catch (error) {
    console.error('封禁/解封失败:', error);
    alert('封禁/解封失败: ' + error.message);
  }
}

// 删除��户
async function deleteUser(userId) {
  if (!confirm('确定要删除该用户吗？')) {
    return;
  }

  try {
    const response = await fetch(`/api/admin/users/${userId}`, {
      method: 'DELETE',
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      alert('删除用户成功');
      await loadUsers();
    } else {
      const error = await response.json();
      alert('删除用户失败: ' + (error.error || '未知错误'));
    }
  } catch (error) {
    console.error('删除用户失败:', error);
    alert('删除用户失败: ' + error.message);
  }
}

// 显示新增用户模态框
function showAddUserModal() {
  const modal = document.getElementById('addUserModal');
  if (modal) {
    modal.style.display = 'block';
  }
}

// 登出
function logout() {
  clearSessionAndRedirect();
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

    let actionButtons = '';
    if (userInfo.isAdmin) {
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
      <td>${user.email || '无'}</td>
      <td>${user.isAdmin ? '管理员' : '普通用户'}</td>
      <td>${user.isBanned ? '已封禁' : '正常'}</td>
      <td>${user.lastLogin ? new Date(user.lastLogin).toLocaleString() : '从未登录'}</td>
      <td>${new Date(user.createdAt).toLocaleString()}</td>
      ${actionButtons}
    `;
    tbody.appendChild(row);
  });
}

// 显示登录审计管理界面
async function viewLoginAudits() {
  const panel = document.getElementById('login-audit-management');
  if (panel.style.display === 'none') {
    panel.style.display = 'block';
    document.getElementById('pending-users-management').style.display = 'none';
    await loadLoginAudits();
  } else {
    panel.style.display = 'none';
  }
}

// 查看待审核用户
async function viewPendingUsers() {
  const panel = document.getElementById('pending-users-management');
  if (panel.style.display === 'none') {
    panel.style.display = 'block';
    document.getElementById('login-audit-management').style.display = 'none';
    await loadPendingUsers();
  } else {
    panel.style.display = 'none';
  }
}

// 加载登录审计
async function loadLoginAudits() {
  showLoading();
  try {
    const response = await fetch('/api/admin/login-audits?limit=15', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const result = await response.json();
      const tbody = document.getElementById('loginAuditTableBody');
      tbody.innerHTML = '';
      result.data.forEach(item => {
        const row = document.createElement('tr');
        row.innerHTML = `
          <td>${item.username}</td>
          <td>${new Date(item.createdAt).toLocaleString()}</td>
          <td>${item.ipAddress || 'unknown'}</td>
          <td>${item.device || 'unknown'}</td>
          <td>${item.operatingSystem || 'unknown'}</td>
          <td>${item.passwordHash || 'unknown'}</td>
        `;
        tbody.appendChild(row);
      });
    } else {
      const error = await response.json();
      alert('获取登录审计失败: ' + error.error);
    }
  } catch (error) {
    console.error('加载登录审计失败:', error);
    alert('加载登录审计失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 加载待审核用户
async function loadPendingUsers() {
  showLoading();
  try {
    const response = await fetch('/api/admin/pending-users', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (response.ok) {
      const users = await response.json();
      const tbody = document.getElementById('pendingUsersTableBody');
      tbody.innerHTML = '';

      if (!users.length) {
        tbody.innerHTML = '<tr><td colspan="5">暂无待审核用户</td></tr>';
        return;
      }

      users.forEach(user => {
        const row = document.createElement('tr');
        row.innerHTML = `
          <td>${user.id}</td>
          <td>${user.username}</td>
          <td>${user.email || '无'}</td>
          <td>${new Date(user.createdAt).toLocaleString()}</td>
          <td>
            <button class="btn btn-success btn-sm" onclick="approveUser(${user.id}, true)">通过</button>
            <button class="btn btn-danger btn-sm" onclick="approveUser(${user.id}, false)">拒绝</button>
          </td>
        `;
        tbody.appendChild(row);
      });
    } else {
      const error = await response.json();
      alert('获取待审核用户失败: ' + error.error);
    }
  } catch (error) {
    console.error('加载待审核用户失败:', error);
    alert('加载待审核用户失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

async function approveUser(userId, isApproved) {
  showLoading();
  try {
    const response = await fetch(`/api/admin/users/${userId}/approve`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ approve: isApproved })
    });

    if (response.ok) {
      alert(isApproved ? '已通过审核' : '已拒绝审核');
      await loadPendingUsers();
    } else {
      const error = await response.json();
      alert('审核失败: ' + error.error);
    }
  } catch (error) {
    console.error('审核用户失败:', error);
    alert('审核用户失败: ' + error.message);
  } finally {
    hideLoading();
  }
}

// 兼容原有函数名
async function loadPendingUsersList() {
  await loadPendingUsers();
}

// 注册新用户
async function addUser(event) {
  event.preventDefault();
  showLoading();

  const username = document.getElementById('newUserUsername').value;
  const password = document.getElementById('newUserPassword').value;
  const isAdmin = document.getElementById('newUserIsAdmin').value === 'true';
  const email = document.getElementById('newUserEmail')?.value || '';

  try {
    const response = await fetch('/api/admin/users', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ username, email, password, isAdmin })
    });

    if (response.ok) {
      alert('用户注册成功');
      closeModal('addUserModal');
      await loadUsers();
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

// 之前登录审计串接
async function showLoginAuditManagement() {
  await viewLoginAudits();
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
    const allData = await loadAllDataForAnalysis();
    const selectedText = (document.getElementById('analysisSelectionInput')?.value || '').trim();
    const data = selectedText ? getAnalysisDataset(allData) : allData;

    if (!data.length) {
      analysisContent.innerHTML = selectedText
        ? '<p>当前编号范围内没有符合条件的人，请检查选择范围是否正确</p>'
        : '<p>暂无数据可分析</p>';
      return;
    }

    const summary = buildAnalysisSummary(data);
    const malePercent = summary.total ? ((summary.male / summary.total) * 100).toFixed(1) : '0.0';
    const femalePercent = summary.total ? ((summary.female / summary.total) * 100).toFixed(1) : '0.0';

    analysisContent.innerHTML = `
      <div style="margin-bottom: 12px; font-size: 13px; color: #475569;">
        当前分析数据范围：${data.length} 条记录
      </div>
      <div style="display:grid; grid-template-columns: repeat(auto-fit, minmax(150px, 1fr)); gap: 12px; margin-bottom: 16px;">
        <div style="background:#f8fafc; border:1px solid #e2e8f0; border-radius:10px; padding: 14px;">
          <div style="font-size:12px; color:#64748b;">总记录数</div>
          <div style="font-size:28px; font-weight:700; margin-top:6px;">${summary.total}</div>
        </div>
        <div style="background:#eff6ff; border:1px solid #bfdbfe; border-radius:10px; padding: 14px;">
          <div style="font-size:12px; color:#1d4ed8;">男性</div>
          <div style="font-size:28px; font-weight:700; margin-top:6px;">${summary.male}</div>
          <div style="font-size:12px; color:#475569;">${malePercent}%</div>
        </div>
        <div style="background:#fdf2f8; border:1px solid #fbcfe8; border-radius:10px; padding: 14px;">
          <div style="font-size:12px; color:#be185d;">女性</div>
          <div style="font-size:28px; font-weight:700; margin-top:6px;">${summary.female}</div>
          <div style="font-size:12px; color:#475569;">${femalePercent}%</div>
        </div>
        <div style="background:#ecfdf5; border:1px solid #bbf7d0; border-radius:10px; padding: 14px;">
          <div style="font-size:12px; color:#15803d;">已填写身份证</div>
          <div style="font-size:28px; font-weight:700; margin-top:6px;">${summary.fieldCompleteness['身份证号'] || '0.0'}%</div>
        </div>
      </div>

      <div style="display:grid; grid-template-columns: 1.2fr 1fr; gap: 16px; margin-bottom: 16px;">
        <div style="background:#fff; border:1px solid #e2e8f0; border-radius:10px; padding: 14px;">
          <h3 style="margin:0 0 12px; font-size:16px;">年龄分布</h3>
          ${renderBarList(Object.entries(summary.ageGroups), '#4f46e5')}
        </div>
        <div style="background:#fff; border:1px solid #e2e8f0; border-radius:10px; padding: 14px;">
          <h3 style="margin:0 0 12px; font-size:16px;">地域分布</h3>
          ${summary.locationEntries.length ? renderBarList(summary.locationEntries, '#10b981') : '<p>暂无可分析地区信息</p>'}
        </div>
      </div>

      <div style="background:#fff; border:1px solid #e2e8f0; border-radius:10px; padding: 14px; margin-bottom: 16px;">
        <h3 style="margin:0 0 12px; font-size:16px;">字段完整度</h3>
        ${renderFieldCompleteness(summary.fieldCompleteness)}
      </div>

      <div style="background:#fff; border:1px solid #e2e8f0; border-radius:10px; padding: 14px;">
        <h3 style="margin:0 0 12px; font-size:16px;">最近10条记录</h3>
        <div style="overflow:auto;">
          <table style="width:100%; border-collapse:collapse; font-size:12px;">
            <thead>
              <tr style="background:#f8fafc;">
                <th style="padding:8px; border:1px solid #e2e8f0; text-align:left;">编号</th>
                <th style="padding:8px; border:1px solid #e2e8f0; text-align:left;">姓名</th>
                <th style="padding:8px; border:1px solid #e2e8f0; text-align:left;">性别</th>
                <th style="padding:8px; border:1px solid #e2e8f0; text-align:left;">年龄</th>
                <th style="padding:8px; border:1px solid #e2e8f0; text-align:left;">电话</th>
              </tr>
            </thead>
            <tbody>
              ${summary.recent.map(item => `
                <tr>
                  <td style="padding:8px; border:1px solid #e2e8f0;">${item['编号'] || '-'}</td>
                  <td style="padding:8px; border:1px solid #e2e8f0;">${item['姓名'] || '-'}</td>
                  <td style="padding:8px; border:1px solid #e2e8f0;">${item['性别'] || '-'}</td>
                  <td style="padding:8px; border:1px solid #e2e8f0;">${getAgeFromBirth(item['出生年月']) ?? '-'}</td>
                  <td style="padding:8px; border:1px solid #e2e8f0;">${item['联系电话'] || '-'}</td>
                </tr>
              `).join('')}
            </tbody>
          </table>
        </div>
      </div>
    `;
  } catch (error) {
    console.error('加载数据分析失败:', error);
    analysisContent.innerHTML = '<p>加载数据分析失败</p>';
  }
}

async function loadAllDataForAnalysis() {
  if (fullAnalysisData.length) {
    return fullAnalysisData;
  }

  try {
    const pageSize = 1000;
    let page = 1;
    const allRows = [];

    while (true) {
      const response = await fetch(`/api/data/persons?page=${page}&limit=${pageSize}&search=`, {
        headers: {
          'Authorization': 'Bearer ' + localStorage.getItem('token')
        }
      });

      if (!response.ok) {
        break;
      }

      const result = await response.json();
      const rows = Array.isArray(result.data) ? result.data : [];
      if (!rows.length) {
        break;
      }

      allRows.push(...rows);
      if (allRows.length >= Number(result.total || allRows.length)) {
        break;
      }
      page += 1;
    }

    fullAnalysisData = allRows;
    return fullAnalysisData;
  } catch (error) {
    console.error('加载全部分析数据失败:', error);
    return [];
  }
}

function getAnalysisDataset(allData) {
  const input = document.getElementById('analysisSelectionInput');
  const selected = parseAnalysisSelection(input ? input.value : '');

  if (!selected.length) {
    return Array.isArray(allData) ? allData : [];
  }

  const selectedSet = new Set(selected.map(id => Number(id)));
  return (Array.isArray(allData) ? allData : []).filter(item => {
    const itemId = Number(item.id ?? item['编号']);
    return !Number.isNaN(itemId) && selectedSet.has(itemId);
  });
}

function parseAnalysisSelection(rawText) {
  const text = String(rawText || '').trim();
  if (!text) {
    return [];
  }

  const ids = new Set();
  const parts = text.split(/[，,\s]+/).filter(Boolean);

  parts.forEach(part => {
    const trimmed = part.trim();
    if (!trimmed) return;

    if (trimmed.includes('-')) {
      const [startStr, endStr] = trimmed.split('-');
      const start = Number(startStr.trim());
      const end = Number(endStr.trim());
      if (!Number.isNaN(start) && !Number.isNaN(end)) {
        const min = Math.min(start, end);
        const max = Math.max(start, end);
        for (let i = min; i <= max; i++) {
          ids.add(i);
        }
      }
      return;
    }

    const id = Number(trimmed);
    if (!Number.isNaN(id)) {
      ids.add(id);
    }
  });

  return Array.from(ids).sort((a, b) => a - b);
}

function resetAnalysisSelection() {
  const input = document.getElementById('analysisSelectionInput');
  if (input) input.value = '';
  loadAnalysis();
}

function getAgeFromBirth(dateValue) {
  if (!dateValue) return null;
  const birth = new Date(dateValue);
  if (Number.isNaN(birth.getTime())) return null;

  const today = new Date();
  let age = today.getFullYear() - birth.getFullYear();
  const monthDiff = today.getMonth() - birth.getMonth();
  if (monthDiff < 0 || (monthDiff === 0 && today.getDate() < birth.getDate())) {
    age--;
  }
  return age;
}

function renderBarList(entries, color) {
  if (!Array.isArray(entries) || !entries.length) {
    return '<p>暂无数据</p>';
  }

  const max = Math.max(...entries.map(([_, value]) => Number(value) || 0), 1);
  return entries.map(([label, value]) => `
    <div style="margin-bottom: 10px;">
      <div style="display:flex; justify-content:space-between; margin-bottom:4px; font-size:12px; color:#475569;">
        <span>${label}</span>
        <span>${value}</span>
      </div>
      <div style="height:8px; background:#e2e8f0; border-radius:999px; overflow:hidden;">
        <div style="height:100%; width:${((Number(value) || 0) / max) * 100}%; background:${color}; border-radius:999px;"></div>
      </div>
    </div>
  `).join('');
}

function renderFieldCompleteness(fieldCompleteness) {
  const entries = Object.entries(fieldCompleteness || {});
  if (!entries.length) {
    return '<p>暂无字段完整度信息</p>';
  }

  return entries.map(([field, value]) => `
    <div style="margin-bottom: 10px;">
      <div style="display:flex; justify-content:space-between; margin-bottom:4px; font-size:12px; color:#475569;">
        <span>${field}</span>
        <span>${value}%</span>
      </div>
      <div style="height:8px; background:#e2e8f0; border-radius:999px; overflow:hidden;">
        <div style="height:100%; width:${Number(value) || 0}%; background:#22c55e; border-radius:999px;"></div>
      </div>
    </div>
  `).join('');
}

function buildAnalysisSummary(data) {
  const records = Array.isArray(data) ? data : [];
  const total = records.length;
  const male = records.filter(item => String(item['性别'] || '').includes('男')).length;
  const female = records.filter(item => String(item['性别'] || '').includes('女')).length;

  const ageGroups = {};
  const locationMap = {};
  const fieldNames = ['编号', '姓名', '性别', '身份证号', '出生年月', '联系电话', '工作单位', '通讯地址'];
  const fieldCompleteness = {};

  records.forEach(item => {
    const age = getAgeFromBirth(item['出生年月']);
    if (age !== null && age >= 0) {
      const group = age < 30 ? '18-29' : age < 45 ? '30-44' : age < 60 ? '45-59' : '60+';
      ageGroups[group] = (ageGroups[group] || 0) + 1;
    }

    const location = item['通讯地址'] || item['工作单位'] || '未知';
    const locationKey = String(location).trim() || '未知';
    locationMap[locationKey] = (locationMap[locationKey] || 0) + 1;
  });

  fieldNames.forEach(field => {
    const filled = records.filter(item => {
      const value = item[field];
      return value !== null && value !== undefined && String(value).trim() !== '' && String(value).trim() !== '无';
    }).length;
    fieldCompleteness[field] = total ? Number(((filled / total) * 100).toFixed(1)) : 0;
  });

  return {
    total,
    male,
    female,
    ageGroups,
    locationEntries: Object.entries(locationMap).sort((a, b) => b[1] - a[1]).slice(0, 8),
    fieldCompleteness,
    recent: records.slice(-10).reverse()
  };
}

const defaultPermissionConfig = {
  dataManagement: {
    label: '数据管理',
    enabled: { label: '是否拥有权限', type: 'group', group: 'dataManagement' },
    items: [
      { key: 'addData', label: '添加数据' },
      { key: 'editData', label: '编辑数据' },
      { key: 'deleteData', label: '删除数据' },
      { key: 'downloadData', label: '载数据' },
      { key: 'uploadData', label: '上传数据' }
    ]
  },
  changeInfo: {
    label: '更换信息',
    enabled: { label: '是否拥有权限', type: 'group', group: 'changeInfo' },
    items: [
      { key: 'changePassword', label: '修改密码' },
      { key: 'changeUsername', label: '修改用户名' }
    ]
  },
  enterAdmin: {
    label: '进入后台',
    enabled: { label: '是否拥有权限', type: 'group', group: 'enterAdmin' },
    items: []
  },
  userManagement: {
    label: '用户管理',
    enabled: { label: '是否拥有权限', type: 'group', group: 'userManagement' },
    items: [
      { key: 'viewUsers', label: '查看用户' },
      { key: 'manageUsers', label: '管理用户' },
      { key: 'registerUsers', label: '注册用户' }
    ]
  },
  registrationManagement: {
    label: '注册管理',
    enabled: { label: '是否拥有权限', type: 'group', group: 'registrationManagement' },
    items: [
      { key: 'viewTokens', label: '查看口令' },
      { key: 'generateTokens', label: '生成口令' },
      { key: 'viewLoginAudit', label: '登录审计' },
      { key: 'reviewUsers', label: '审核用户' }
    ]
  }
};

function getPermissionSnapshot() {
  return JSON.parse(JSON.stringify(defaultPermissionConfig));
}

function mergePermissions(basePermissions = {}, incomingPermissions = {}) {
  const snapshot = getPermissionSnapshot();
  Object.keys(snapshot).forEach(groupKey => {
    const group = snapshot[groupKey];
    const sourceGroup = incomingPermissions[groupKey] || {};
    group.enabled = !!(sourceGroup.enabled !== undefined ? sourceGroup.enabled : false);
    if (group.items && group.items.length) {
      group.items.forEach(item => {
        item.enabled = !!(sourceGroup[item.key] !== undefined ? sourceGroup[item.key] : false);
      });
    }
    if (group.group === 'enterAdmin') {
      group.enabled = !!(sourceGroup.enabled !== undefined ? sourceGroup.enabled : false);
    }
    if (basePermissions[groupKey]) {
      group.enabled = !!(basePermissions[groupKey].enabled || sourceGroup.enabled);
      if (group.items && group.items.length) {
        group.items.forEach(item => {
          const baseValue = basePermissions[groupKey][item.key];
          item.enabled = !!(baseValue || sourceGroup[item.key]);
        });
      }
    }
  });
  return snapshot;
}

function normalizePermissionState(rawPermissions = {}) {
  const snapshot = getPermissionSnapshot();
  const normalized = JSON.parse(JSON.stringify(snapshot));

  Object.keys(snapshot).forEach(groupKey => {
    const group = normalized[groupKey];
    const sourceGroup = rawPermissions[groupKey] || {};
    group.enabled = Boolean(sourceGroup.enabled);

    if (group.items && group.items.length) {
      group.items.forEach(item => {
        item.enabled = Boolean(sourceGroup[item.key]);
      });
    }
  });

  return normalized;
}

function getPermissionMatrixFromUser(user) {
  const rawPermissions = user && user.permissions ? user.permissions : {};
  const normalized = normalizePermissionState(rawPermissions);

  Object.keys(normalized).forEach(groupKey => {
    const group = normalized[groupKey];
    const sourceGroup = rawPermissions[groupKey] || {};
    group.enabled = Boolean(sourceGroup.enabled !== undefined ? sourceGroup.enabled : false);
    if (group.items && group.items.length) {
      group.items.forEach(item => {
        item.enabled = Boolean(sourceGroup[item.key] !== undefined ? sourceGroup[item.key] : false);
      });
    }
  });

  return normalized;
}

function renderPermissionTable(user) {
  const tableBody = document.getElementById('userPermissionsTableBody');
  const container = document.getElementById('userPermissionsTableContainer');
  if (!tableBody || !container) return;

  const selectedUser = user || { permissions: {} };
  const permissionMatrix = getPermissionMatrixFromUser(selectedUser);
  const rows = [];

  Object.keys(permissionMatrix).forEach(groupKey => {
    const group = permissionMatrix[groupKey];
    const groupEnabled = !!group.enabled;
    const detailHtml = (group.items || []).map(item => `
      <label style="display:inline-flex; align-items:center; gap:6px; margin: 4px 10px 4px 0; min-width: 130px;">
        <input type="checkbox" data-group="${groupKey}" data-key="${item.key}" ${item.enabled ? 'checked' : ''}>
        <span>${item.label}</span>
      </label>
    `).join('');

    rows.push(`
      <tr>
        <td><input type="checkbox" data-group="${groupKey}" data-enabled="true" ${groupEnabled ? 'checked' : ''}></td>
        <td>${group.label}</td>
        <td>${detailHtml || '<span style="color:#64748b;">无细分权限</span>'}</td>
      </tr>
    `);
  });

  tableBody.innerHTML = rows.join('');
  container.style.display = selectedUser.id ? 'block' : 'none';
}

async function loadPermissionUserOptions() {
  try {
    const response = await fetch('/api/admin/users', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (!response.ok) {
      throw new Error('加载用户列表失败');
    }

    const users = await response.json();
    const select = document.getElementById('permissionUserSelect');
    if (!select) return;

    select.innerHTML = '<option value="">请选择用户</option>' + users.map(user => `
      <option value="${user.id}">${user.username}${user.isAdmin ? '（管理员）' : ''}</option>
    `).join('');

    if (users.length) {
      select.value = users[0] ? String(users[0].id) : '';
      const selected = users.find(user => String(user.id) === select.value) || users[0];
      renderPermissionTable(selected);
    } else {
      renderPermissionTable({ permissions: {} });
    }
  } catch (error) {
    console.error('加载用户权限列表失败:', error);
    alert('加载用户权限列表失败: ' + error.message);
  }
}

async function onPermissionUserChange() {
  const select = document.getElementById('permissionUserSelect');
  if (!select || !select.value) {
    renderPermissionTable({ permissions: {} });
    return;
  }

  try {
    const response = await fetch('/api/admin/users', {
      headers: {
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      }
    });

    if (!response.ok) {
      throw new Error('获取用户信息失败');
    }

    const users = await response.json();
    const user = users.find(item => String(item.id) === String(select.value));
    renderPermissionTable(user || { permissions: {} });
  } catch (error) {
    console.error('切换权限用户失败:', error);
    alert('切换用户失败: ' + error.message);
  }
}

async function saveUserPermissions() {
  const select = document.getElementById('permissionUserSelect');
  if (!select || !select.value) {
    alert('请选择要修改权限的用户');
    return;
  }

  const permissionMatrix = {};
  const checkboxList = document.querySelectorAll('#userPermissionsTableBody input[type="checkbox"]');

  checkboxList.forEach(checkbox => {
    const groupKey = checkbox.dataset.group;
    const itemKey = checkbox.dataset.key;
    const isGroupToggle = checkbox.dataset.enabled === 'true';

    if (!groupKey) return;
    if (!permissionMatrix[groupKey]) {
      permissionMatrix[groupKey] = {};
    }

    if (isGroupToggle) {
      permissionMatrix[groupKey].enabled = checkbox.checked;
      return;
    }

    if (itemKey) {
      permissionMatrix[groupKey][itemKey] = checkbox.checked;
    }
  });

  try {
    const response = await fetch(`/api/admin/users/${select.value}/permissions`, {
      method: 'PUT',
      headers: {
        'Content-Type': 'application/json',
        'Authorization': 'Bearer ' + localStorage.getItem('token')
      },
      body: JSON.stringify({ permissions: permissionMatrix })
    });

    if (!response.ok) {
      const error = await response.json();
      throw new Error(error.error || '保存权限失败');
    }

    alert('用户权限已保存');
    await onPermissionUserChange();
  } catch (error) {
    console.error('保存用户权限失败:', error);
    alert('保存用户权限失败: ' + error.message);
  }
}

function bindPermissionEvents() {
  const userSelect = document.getElementById('permissionUserSelect');
  if (userSelect) {
    userSelect.onchange = onPermissionUserChange;
  }

  document.addEventListener('change', function (event) {
    const target = event.target;
    if (!(target instanceof HTMLInputElement) || !target.dataset.group) return;

    const groupKey = target.dataset.group;
    if (target.dataset.enabled === 'true') {
      const related = document.querySelectorAll(`#userPermissionsTableBody input[data-group="${groupKey}"]`);
      related.forEach(item => {
        if (item !== target) {
          item.disabled = !target.checked;
        }
      });
    }
  });
}

// in initPage() after admin item toggle
if (userInfo.isAdmin) {
  const adminItems = document.querySelectorAll('.admin-only');
  adminItems.forEach(item => {
    item.style.display = 'block';
  });
  setTimeout(() => {
    loadPermissionUserOptions();
    bindPermissionEvents();
  }, 0);
}
