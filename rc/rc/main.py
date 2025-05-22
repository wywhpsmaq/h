import os
import sys
import tkinter as tk
import tkinter.font as tkfont
from tkinter import messagebox, filedialog
from utils import encrypt, decrypt, check_password, load_data, save_data, get_person_info, save_passwords, load_passwords
import subprocess
import json
if getattr(sys, 'frozen', False):
    BASE_DIR = os.path.dirname(sys.executable)
else:
    BASE_DIR = os.path.dirname(__file__)
DATA_DIR = os.path.join(BASE_DIR, 'data')
ICON_PATH = os.path.join(BASE_DIR, 'assets', '1.png')
CARD_IMG_PATH = os.path.join(BASE_DIR, 'assets', '2.png')
PASS_FILE = os.path.join(DATA_DIR, 'password.dat')
ADMIN_PASS = 'wywhpsmaq17726428322'
STYLE_PATH = os.path.join(BASE_DIR, 'style.json')
with open(STYLE_PATH, 'r', encoding='utf-8') as f:
    STYLE = json.load(f)
class LoginWindow(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('信息查找软件')
        self.geometry('400x300')
        self.configure(bg='white')
        self.icon_img = tk.PhotoImage(file=ICON_PATH)
        self.iconphoto(False, self.icon_img)
        self.step = 0
        self.passwords = load_passwords()
        if not self.passwords:
            self.passwords = ['114514', '123456789']
            save_passwords(self.passwords)
        self.input_pass = ''
        self.is_admin = False
        self.create_widgets()
    def create_widgets(self):
        tk.Label(self, text='欢迎访问', fg='blue', bg='white', font=('微软雅黑', 20)).pack(pady=20)
        self.pass_entry = tk.Entry(self, show='*', font=('微软雅黑', 16))
        self.pass_entry.pack(pady=10)
        self.pass_entry.focus()
        self.pass_entry.bind('<Return>', lambda e: self.check_pass())
        self.btn = tk.Button(self, text='下一步', command=self.check_pass, bg='#2196F3', fg='white', font=('微软雅黑', 12))
        self.btn.pack(pady=10)
        self.admin_btn = tk.Button(self, text='以管理员身份登录', command=self.admin_login, bg='#1976D2', fg='white', font=('微软雅黑', 11))
        self.admin_btn.pack(pady=5)
        self.forget_label = tk.Label(self, text='忘记密码', fg='gray', bg='white', cursor='hand2')
        self.forget_label.pack(side='bottom', pady=10)
        self.forget_label.bind('<Button-1>', lambda e: self.change_password())
    def check_pass(self):
        pwd = self.pass_entry.get()
        if pwd == self.passwords[self.step]:
            self.step += 1
            if self.step == 2:
                messagebox.showinfo('提示', '算法结构来自Wywhpsmaq，数据来自David')
                self.destroy()
                MainWindow(is_admin=self.is_admin).mainloop()
            else:
                self.pass_entry.delete(0, 'end')
                messagebox.showinfo('提示', '请继续输入第二个密码')
        else:
            messagebox.showerror('错误', '密码错误')
            self.pass_entry.delete(0, 'end')
    def admin_login(self):
        def do_admin():
            pwd = admin_entry.get()
            if pwd == ADMIN_PASS:
                self.is_admin = True
                messagebox.showinfo('成功', '欢迎伟大的管理员！！！')
                self.destroy()
                MainWindow(is_admin=True).mainloop()
            else:
                messagebox.showerror('错误', '管理员密码错误')
        win = tk.Toplevel(self)
        win.title('管理员登录')
        tk.Label(win, text='请输入管理员密码:').pack(pady=10)
        admin_entry = tk.Entry(win, show='*', font=('微软雅黑', 12))
        admin_entry.pack(pady=5)
        admin_entry.focus()
        tk.Button(win, text='确定', command=do_admin).pack(pady=10)
    def change_password(self):
        def do_change():
            admin_pwd = admin_entry.get()
            if admin_pwd == ADMIN_PASS:
                new_pwd = new_entry.get()
                if new_pwd:
                    self.passwords[0] = new_pwd
                    save_passwords(self.passwords)
                    messagebox.showinfo('成功', '密码已修改')
                    win.destroy()
                else:
                    messagebox.showerror('错误', '新密码不能为空')
            else:
                messagebox.showerror('错误', '管理员密码错误')
        win = tk.Toplevel(self)
        win.title('修改密码')
        tk.Label(win, text='管理员密码:').pack()
        admin_entry = tk.Entry(win, show='*')
        admin_entry.pack()
        tk.Label(win, text='新密码:').pack()
        new_entry = tk.Entry(win, show='*')
        new_entry.pack()
        tk.Button(win, text='确定', command=do_change).pack()
class MainWindow(tk.Tk):
    def __init__(self, is_admin=False):
        super().__init__()
        self.title('信息查找软件')
        self.geometry('900x600')
        self.minsize(900, 600)
        self.icon_img = tk.PhotoImage(file=ICON_PATH)
        self.iconphoto(False, self.icon_img)
        self.data = load_data()
        self.is_admin = is_admin
        self.main_frame = tk.Frame(self, bg=STYLE['main_bg'], bd=2, relief='groove')
        self.main_frame.pack(fill='both', expand=True)
        self.create_widgets()
    def create_widgets(self):
        top_frame = tk.Frame(self.main_frame, bg=STYLE['top_bg'], bd=2, relief='ridge', highlightbackground=STYLE['top_border'], highlightthickness=2)
        top_frame.pack(fill='x', pady=12, padx=12, ipady=6)
        self.search_vars = {}
        fields = ['序号', '姓名', '性别', '身份证号', '出生日期', '地点', '年龄']
        font_label = tkfont.Font(family=STYLE['font_family'], size=STYLE['font_size'], weight='bold' if STYLE.get('font_bold') else 'normal')
        font_entry = tkfont.Font(family=STYLE['font_family'], size=STYLE['font_entry_size'])
        for i, field in enumerate(fields):
            tk.Label(top_frame, text=field, bg=STYLE['top_bg'], font=font_label).grid(row=0, column=i*2, padx=2)
            var = tk.StringVar()
            self.search_vars[field] = var
            ent = tk.Entry(top_frame, textvariable=var, width=10, font=font_entry, relief='groove', bd=2)
            ent.grid(row=0, column=i*2+1, padx=2)
        def style_btn(btn):
            btn.configure(bg=STYLE['button_bg'], fg=STYLE['button_fg'], activebackground=STYLE['button_active_bg'], activeforeground=STYLE['button_active_fg'], font=(STYLE['font_family'], STYLE['font_size'], 'bold'), bd=0, relief='ridge', cursor='hand2')
        btns = []
        btns.append(tk.Button(top_frame, text='查找', command=self.search))
        btns.append(tk.Button(top_frame, text='导出数据', command=self.export_data))
        btns.append(tk.Button(top_frame, text='导入数据', command=self.import_data))
        btns.append(tk.Button(top_frame, text='添加数据', command=self.add_data))
        btns.append(tk.Button(top_frame, text='删除数据', command=self.delete_data))
        btns.append(tk.Button(top_frame, text='整理数据', command=self.clean_data))
        btns.append(tk.Button(top_frame, text='数据分析', command=self.analyze_data))
        for idx, btn in enumerate(btns):
            style_btn(btn)
            btn.grid(row=0, column=14+idx*2, padx=6)
        for btn in btns:
            btn.bind('<Enter>', lambda e, b=btn: b.config(bg=STYLE['button_active_bg']))
            btn.bind('<Leave>', lambda e, b=btn: b.config(bg=STYLE['button_bg']))
        # 在按钮区最后加一个“公示”按钮，并与前面按钮有间隔
        notice_btn = tk.Button(top_frame, text='公示', command=self.show_notice, bg='#1976D2', fg='white', font=('微软雅黑', 11, 'bold'), bd=0, relief='ridge', cursor='hand2')
        style_btn(notice_btn)
        notice_btn.grid(row=0, column=14+len(btns)*2, padx=(30, 0))  # 与前面按钮有较大间隔
        list_frame_outer = tk.Frame(self.main_frame, bg=STYLE['main_bg'])
        list_frame_outer.pack(fill='both', expand=True, padx=12, pady=8)
        canvas = tk.Canvas(list_frame_outer, bg=STYLE['main_bg'], highlightthickness=0)
        scrollbar = tk.Scrollbar(list_frame_outer, orient='vertical', command=canvas.yview)
        self.list_frame = tk.Frame(canvas, bg=STYLE['main_bg'])
        self.list_frame.bind(
            '<Configure>',
            lambda e: canvas.configure(scrollregion=canvas.bbox('all'))
        )
        canvas.create_window((0, 0), window=self.list_frame, anchor='nw')
        canvas.configure(yscrollcommand=scrollbar.set)
        canvas.pack(side='left', fill='both', expand=True)
        scrollbar.pack(side='right', fill='y')
        list_frame_outer.pack_propagate(False)
        self.refresh_list(self.data)
    def refresh_list(self, data):
        for widget in self.list_frame.winfo_children():
            widget.destroy()
        headers = ['序号', '姓名', '性别', '身份证号', '出生日期', '地点', '年龄']
        font_header = tkfont.Font(family=STYLE['font_family'], size=STYLE['font_size'], weight='bold' if STYLE.get('font_bold') else 'normal')
        font_row = tkfont.Font(family=STYLE['font_family'], size=STYLE['font_size'])
        for i, h in enumerate(headers):
            tk.Label(self.list_frame, text=h, bg=STYLE['header_bg'], fg=STYLE['header_fg'], font=font_header, borderwidth=1, relief='ridge', padx=6, pady=4).grid(row=0, column=i, sticky='nsew')
        for idx, person in enumerate(data):
            row_bg = STYLE['row_bg1'] if idx % 2 == 0 else STYLE['row_bg2']
            for j, key in enumerate(headers):
                val = person.get(key, '')
                l = tk.Label(self.list_frame, text=val, bg=row_bg, font=font_row, borderwidth=1, relief='ridge', padx=4, pady=2)
                l.grid(row=idx+1, column=j, sticky='nsew')
                l.bind('<Button-1>', lambda e, p=person: self.show_card(p))
    def search(self):
        result = self.data
        for k, v in self.search_vars.items():
            val = v.get().strip()
            if val:
                result = [p for p in result if str(p.get(k, '')).find(val) != -1]
        self.refresh_list(result)
    def resolve_conflict(self, new_person, exist_person):
        win = tk.Toplevel(self)
        win.title('数据冲突处理')
        tk.Label(win, text='检测到数据冲突（序号或身份证号重复）').pack(pady=5)
        tk.Label(win, text=f"现有数据: {exist_person}").pack(pady=2)
        tk.Label(win, text=f"导入/添加数据: {new_person}").pack(pady=2)
        result = {'action': None}
        def set_action(a):
            result['action'] = a
            win.destroy()
        btns = [
            ('保留导入数据', 'keep_new'),
            ('保留现有数据', 'keep_exist'),
            ('修改导入数据', 'edit_new'),
            ('修改现有数据', 'edit_exist'),
            ('全部删除', 'delete_both')
        ]
        for text, val in btns:
            tk.Button(win, text=text, command=lambda v=val: set_action(v)).pack(fill='x', padx=10, pady=2)
        win.grab_set()
        self.wait_window(win)
        return result['action']
    def import_data(self):
        file_path = filedialog.askopenfilename(filetypes=[('CSV文件', '*.csv')])
        if not file_path:
            return
        import csv
        for encoding in ('utf-8', 'gbk'):
            try:
                with open(file_path, 'r', encoding=encoding) as f:
                    reader = csv.DictReader(f)
                    field_map = {}
                    for k in reader.fieldnames:
                        k_strip = k.strip().replace('\ufeff', '')
                        if k_strip in ['序号', '编号', 'ID', 'id', 'Id']:
                            field_map['序号'] = k
                        elif k_strip in ['姓名', '名字', 'name', 'Name']:
                            field_map['姓名'] = k
                        elif k_strip in ['性别', 'gender', 'Gender']:
                            field_map['性别'] = k
                        elif k_strip in ['身份证号', '身份证', '证件号', '身份证号码']:
                            field_map['身份证号'] = k
                        elif k_strip in ['出生日期', '生日', 'birth', 'Birth']:
                            field_map['出生日期'] = k
                        elif k_strip in ['地点', '地址', '户籍', 'location', 'Location']:
                            field_map['地点'] = k
                        elif k_strip in ['年龄', 'age', 'Age']:
                            field_map['年龄'] = k
                    idx = len(self.data) + 1
                    for row in reader:
                        person = {}
                        for std_key in ['序号', '姓名', '性别', '身份证号', '出生日期', '地点', '年龄']:
                            val = row.get(field_map.get(std_key, ''), '').strip() if field_map.get(std_key) else ''
                            person[std_key] = val
                        if not person['序号']:
                            person['序号'] = str(idx)
                        idx += 1
                        exist = next((p for p in self.data if p.get('序号') == person['序号'] or (person['身份证号'] and p.get('身份证号') == person['身份证号'])), None)
                        if exist:
                            action = self.resolve_conflict(person, exist)
                            if action == 'keep_new':
                                self.data.remove(exist)
                                self.data.append(person)
                            elif action == 'keep_exist':
                                pass
                            elif action == 'edit_new':
                                self.edit_person(self, person)
                                self.data.remove(exist)
                                self.data.append(person)
                            elif action == 'edit_exist':
                                self.edit_person(self, exist)
                            elif action == 'delete_both':
                                self.data.remove(exist)
                        else:
                            self.data.append(person)
                save_data(self.data)
                self.refresh_list(self.data)
                messagebox.showinfo('导入成功', f'数据已导入（编码：{encoding}）')
                return
            except Exception as e:
                last_error = e
        messagebox.showerror('导入失败', f'无法读取文件，错误信息：{last_error}')
    def add_data(self):
        win = tk.Toplevel(self)
        win.title('添加数据')
        entries = {}
        for i, field in enumerate(['序号', '姓名', '性别', '身份证号']):
            tk.Label(win, text=field).grid(row=i, column=0)
            ent = tk.Entry(win)
            ent.grid(row=i, column=1)
            entries[field] = ent
        def do_add():
            person = {k: entries[k].get().strip() for k in entries}
            birth, loc, age = get_person_info(person['身份证号'])
            person['出生日期'] = birth
            person['地点'] = loc
            person['年龄'] = age
            exist = next((p for p in self.data if p.get('序号') == person['序号'] or (person['身份证号'] and p.get('身份证号') == person['身份证号'])), None)
            if exist:
                action = self.resolve_conflict(person, exist)
                if action == 'keep_new':
                    self.data.remove(exist)
                    self.data.append(person)
                elif action == 'keep_exist':
                    pass
                elif action == 'edit_new':
                    self.edit_person(self, person)
                    self.data.remove(exist)
                    self.data.append(person)
                elif action == 'edit_exist':
                    self.edit_person(self, exist)
                elif action == 'delete_both':
                    self.data.remove(exist)
            else:
                self.data.append(person)
            save_data(self.data)
            self.refresh_list(self.data)
            win.destroy()
        tk.Button(win, text='确定', command=do_add).grid(row=5, column=0, columnspan=2)
    def delete_data(self):
        win = tk.Toplevel(self)
        win.title('删除数据')
        tk.Label(win, text='输入要删除的序号或身份证号（如1-40或1,2,3,4）:').grid(row=0, column=0)
        entry = tk.Entry(win, width=40)
        entry.grid(row=1, column=0)
        def parse_keys(text):
            keys = set()
            for part in text.split(','):
                part = part.strip()
                if '-' in part and part.replace('-', '').isdigit():
                    start, end = part.split('-')
                    if start.isdigit() and end.isdigit():
                        keys.update(str(i) for i in range(int(start), int(end)+1))
                elif part:
                    keys.add(part)
            return keys
        def do_delete():
            raw = entry.get()
            if not raw.strip():
                messagebox.showerror('错误', '请输入要删除的序号或身份证号')
                return
            keys = parse_keys(raw)
            before = len(self.data)
            self.data = [p for p in self.data if p.get('序号','') not in keys and p.get('身份证号','') not in keys]
            save_data(self.data)
            self.refresh_list(self.data)
            win.destroy()
            messagebox.showinfo('删除完成', f'已删除{before - len(self.data)}条数据')
        def check_pwd_and_delete():
            if getattr(self, 'is_admin', False):
                tk.messagebox.showinfo('提示', '已以管理员身份登录，无需再次输入密码')
                do_delete()
            else:
                def check_pwd():
                    pwd = pwd_entry.get()
                    from utils import load_passwords
                    pwds = load_passwords()
                    if pwds and pwd == pwds[0]:
                        pwd_win.destroy()
                        do_delete()
                    else:
                        tk.messagebox.showerror('错误', '密码错误', parent=pwd_win)
                pwd_win = tk.Toplevel(win)
                pwd_win.title('密码验证')
                pwd_win.geometry('260x120')
                pwd_win.resizable(False, False)
                tk.Label(pwd_win, text='请输入第一个登录密码：', font=('微软雅黑', 11)).pack(pady=10)
                pwd_entry = tk.Entry(pwd_win, show='*', font=('微软雅黑', 11))
                pwd_entry.pack(pady=5)
                pwd_entry.focus()
                tk.Button(pwd_win, text='确定', command=check_pwd, font=('微软雅黑', 10)).pack(pady=5)
                def on_cancel_pwd():
                    pwd_win.destroy()
                tk.Button(pwd_win, text='取消', command=on_cancel_pwd, font=('微软雅黑', 10)).pack()
                pwd_win.transient(win)
                pwd_win.grab_set()
        tk.Button(win, text='确定', command=check_pwd_and_delete).grid(row=2, column=0)
    def show_card(self, person):
        win = tk.Toplevel(self)
        win.title('信息卡片')
        win.geometry('420x260')
        win.configure(bg='#e3f2fd')
        win.resizable(False, False)
        win.update_idletasks()
        x = (win.winfo_screenwidth() - 420) // 2
        y = (win.winfo_screenheight() - 260) // 2
        win.geometry(f'+{x}+{y}')
        card_frame = tk.Frame(win, bg='white', bd=3, relief='groove', highlightbackground='#90caf9', highlightthickness=2)
        card_frame.pack(fill='both', expand=True, padx=10, pady=10)
        info_frame = tk.Frame(card_frame, bg='white')
        info_frame.pack(side='top', fill='both', expand=True)
        try:
            bg_img = tk.PhotoImage(file=CARD_IMG_PATH)
            canvas = tk.Canvas(info_frame, width=400, height=140, highlightthickness=0, bg='white')
            canvas.pack(fill='both', expand=True)
            canvas.create_image(0, 0, anchor='nw', image=bg_img)
            info = f"姓名: {person.get('姓名', '')}\n性别: {person.get('性别', '')}\n身份证号: {person.get('身份证号', '')}\n出生日期: {person.get('出生日期', '')}\n地点: {person.get('地点', '')}\n年龄: {person.get('年龄', '')}"
            canvas.create_text(200, 70, text=info, fill='black', font=('Microsoft YaHei UI', 14))
            win.bg_img = bg_img
        except Exception:
            info = f"姓名: {person.get('姓名', '')}\n性别: {person.get('性别', '')}\n身份证号: {person.get('身份证号', '')}\n出生日期: {person.get('出生日期', '')}\n地点: {person.get('地点', '')}\n年龄: {person.get('年龄', '')}"
            tk.Label(info_frame, text=info, font=('Microsoft YaHei UI', 14), bg='white').pack(padx=20, pady=20, fill='both', expand=True)
        btn_frame = tk.Frame(card_frame, bg='white')
        btn_frame.pack(side='bottom', pady=8)
        def style_btn(btn):
            btn.configure(bg='#2196F3', fg='white', activebackground='#1976D2', activeforeground='white', font=('微软雅黑', 11, 'bold'), bd=0, relief='ridge', cursor='hand2')
        btn1 = tk.Button(btn_frame, text='修改数据', command=lambda: self.edit_person(win, person))
        btn2 = tk.Button(btn_frame, text='删除数据', command=lambda: self.delete_person(win, person))
        btn3 = tk.Button(btn_frame, text='kh', command=lambda: self.kh_action(person))
        style_btn(btn1)
        style_btn(btn2)
        style_btn(btn3)
        btn1.pack(side='left', padx=10)
        btn2.pack(side='left', padx=10)
        btn3.pack(side='left', padx=10)
        for btn in [btn1, btn2, btn3]:
            btn.bind('<Enter>', lambda e, b=btn: b.config(bg='#1976D2'))
            btn.bind('<Leave>', lambda e, b=btn: b.config(bg='#2196F3'))
    def kh_action(self, person):
        info = f"姓名: {person.get('姓名', '')}\n性别: {person.get('性别', '')}\n身份证号: {person.get('身份证号', '')}\n出生日期: {person.get('出生日期', '')}\n地点: {person.get('地点', '')}\n年龄: {person.get('年龄', '')}"
        if tk.messagebox.askokcancel('信息确认', info):
            def do_kh_format():
                win = tk.Toplevel(self)
                win.title('kh格式')
                win.geometry('350x220')
                win.resizable(False, False)
                tk.Label(win, text='请选择kh格式：', font=('微软雅黑', 13, 'bold')).pack(pady=10)
                var = tk.StringVar(value='1')
                frame = tk.Frame(win)
                frame.pack(pady=5)
                fmt1 = "1.基本信息\n2.kh来自David\n3.专有IP:225.225.225.225"
                fmt2 = "1.基本信息"
                rb1 = tk.Radiobutton(frame, text='格式一', variable=var, value='1', anchor='w', font=('微软雅黑', 11))
                rb2 = tk.Radiobutton(frame, text='格式二', variable=var, value='2', anchor='w', font=('微软雅黑', 11))
                rb1.grid(row=0, column=0, sticky='w')
                rb2.grid(row=1, column=0, sticky='w')
                tk.Label(frame, text=fmt1, justify='left', font=('微软雅黑', 10), fg='#1976D2').grid(row=0, column=1, sticky='w', padx=8)
                tk.Label(frame, text=fmt2, justify='left', font=('微软雅黑', 10), fg='#1976D2').grid(row=1, column=1, sticky='w', padx=8)
                btn_frame = tk.Frame(win)
                btn_frame.pack(pady=15)
                result = {'ok': False, 'fmt': None}
                def on_ok():
                    fmt = var.get()
                    if fmt == '1':
                        result['ok'] = True
                        result['fmt'] = '1'
                        win.destroy()
                    else:
                        if getattr(self, 'is_admin', False):
                            tk.messagebox.showinfo('提示', '已以管理员身份登录，无需再次输入管理员密码')
                            result['ok'] = True
                            result['fmt'] = '2'
                            win.destroy()
                        else:
                            def check_admin():
                                pwd = pwd_entry.get()
                                if pwd == ADMIN_PASS:
                                    result['ok'] = True
                                    result['fmt'] = '2'
                                    admin_win.destroy()
                                    win.destroy()
                                else:
                                    tk.messagebox.showerror('错误', '管理员密码错误', parent=admin_win)
                            admin_win = tk.Toplevel(win)
                            admin_win.title('管理员密码验证')
                            admin_win.geometry('260x120')
                            admin_win.resizable(False, False)
                            tk.Label(admin_win, text='请输入管理员密码：', font=('微软雅黑', 11)).pack(pady=10)
                            pwd_entry = tk.Entry(admin_win, show='*', font=('微软雅黑', 11))
                            pwd_entry.pack(pady=5)
                            pwd_entry.focus()
                            btn = tk.Button(admin_win, text='确定', command=check_admin, font=('微软雅黑', 10))
                            btn.pack(pady=5)
                            def on_cancel():
                                admin_win.destroy()
                            tk.Button(admin_win, text='取消', command=on_cancel, font=('微软雅黑', 10)).pack()
                            admin_win.transient(win)
                            admin_win.grab_set()
                def on_cancel():
                    win.destroy()
                tk.Button(btn_frame, text='确定', command=on_ok, width=8, font=('微软雅黑', 11)).pack(side='left', padx=10)
                tk.Button(btn_frame, text='取消', command=on_cancel, width=8, font=('微软雅黑', 11)).pack(side='left', padx=10)
                win.transient(self)
                win.grab_set()
                self.wait_window(win)
                return result['ok'], result['fmt']
            ok, fmt = do_kh_format()
            if ok:
                output_dir = os.path.join(BASE_DIR, 'output')
                if not os.path.exists(output_dir):
                    os.makedirs(output_dir)
                kh_txt = os.path.join(output_dir, 'kh.txt')
                with open(kh_txt, 'a', encoding='utf-8') as f:
                    f.write(str(person.get('序号', '')) + '\n')
    def edit_person(self, parent_win, person):
        win = tk.Toplevel(parent_win)
        win.title('修改数据')
        entries = {}
        fields = ['序号', '姓名', '性别', '身份证号', '出生日期', '地点', '年龄']
        for i, field in enumerate(fields):
            tk.Label(win, text=field).grid(row=i, column=0)
            ent = tk.Entry(win)
            ent.insert(0, str(person.get(field, '')))
            ent.grid(row=i, column=1)
            entries[field] = ent
        def do_save():
            new_data = {field: entries[field].get().strip() for field in fields}
            for idx, p in enumerate(self.data):
                if p is person or (p.get('序号') == person.get('序号') and p.get('身份证号') == person.get('身份证号')):
                    self.data[idx] = new_data
                    break
            save_data(self.data)
            self.refresh_list(self.data)
            win.destroy()
            if parent_win.winfo_exists():
                parent_win.destroy()
            tk.messagebox.showinfo('修改成功', '数据已修改')
        tk.Button(win, text='保存', command=do_save).grid(row=len(fields), column=0, columnspan=2)
    def delete_person(self, parent_win, person):
        def do_delete():
            self.data.remove(person)
            save_data(self.data)
            self.refresh_list(self.data)
            parent_win.destroy()
            tk.messagebox.showinfo('删除成功', '数据已删除')
        def check_pwd_and_delete():
            if getattr(self, 'is_admin', False):
                tk.messagebox.showinfo('提示', '已以管理员身份登录，无需再次输入密码')
                do_delete()
            else:
                def check_pwd():
                    pwd = pwd_entry.get()
                    from utils import load_passwords
                    pwds = load_passwords()
                    if pwds and pwd == pwds[0]:
                        pwd_win.destroy()
                        do_delete()
                    else:
                        tk.messagebox.showerror('错误', '密码错误', parent=pwd_win)
                pwd_win = tk.Toplevel(parent_win)
                pwd_win.title('密码验证')
                pwd_win.geometry('260x120')
                pwd_win.resizable(False, False)
                tk.Label(pwd_win, text='请输入第一个登录密码：', font=('微软雅黑', 11)).pack(pady=10)
                pwd_entry = tk.Entry(pwd_win, show='*', font=('微软雅黑', 11))
                pwd_entry.pack(pady=5)
                pwd_entry.focus()
                tk.Button(pwd_win, text='确定', command=check_pwd, font=('微软雅黑', 10)).pack(pady=5)
                def on_cancel_pwd():
                    pwd_win.destroy()
                tk.Button(pwd_win, text='取消', command=on_cancel_pwd, font=('微软雅黑', 10)).pack()
                pwd_win.transient(parent_win)
                pwd_win.grab_set()
        if tk.messagebox.askyesno('确认删除', '确定要删除此条数据吗？'):
            check_pwd_and_delete()
    def clean_data(self):
        for person in self.data:
            birth = person.get('出生日期', '').replace('/', '-').replace('.', '-')
            if len(birth) == 8 and birth.isdigit():
                birth = f"{birth[:4]}-{birth[4:6]}-{birth[6:8]}"
            elif len(birth) == 10 and '-' in birth:
                y, m, d = birth.split('-')
                birth = f"{y.zfill(4)}-{m.zfill(2)}-{d.zfill(2)}"
            person['出生日期'] = birth
        save_data(self.data)
        self.refresh_list(self.data)
        tk.messagebox.showinfo('整理完成', '出生日期已整理完毕')
    def analyze_data(self):
        from collections import Counter
        win = tk.Toplevel(self)
        win.title('数据分析')
        win.geometry('600x600')
        text = tk.Text(win, font=('微软雅黑', 12))
        text.pack(fill='both', expand=True)
        if not self.data:
            text.insert('end', '暂无数据\n')
            return
        sex_list = [p.get('性别', '') for p in self.data if p.get('性别', '')]
        sex_count = Counter(sex_list)
        total = len(self.data)
        text.insert('end', f'【性别分布】\n')
        for k, v in sex_count.items():
            percent = v / total * 100
            bar = '█' * int(percent // 2)
            text.insert('end', f'{k}: {v} ({percent:.1f}%) {bar}\n')
        text.insert('end', '\n')
        loc_list = [p.get('地点', '') for p in self.data if p.get('地点', '')]
        loc_count = Counter(loc_list).most_common(10)
        text.insert('end', f'【地点分布（前10）】\n')
        for k, v in loc_count:
            percent = v / total * 100
            bar = '█' * int(percent // 2)
            text.insert('end', f'{k}: {v} ({percent:.1f}%) {bar}\n')
        text.insert('end', '\n')
        age_list = []
        for p in self.data:
            try:
                age = int(p.get('年龄', ''))
                age_list.append(age)
            except:
                continue
        bins = [(0,11),(12,12),(13,13),(14,30),(31,50),(51,65),(66,75),(76,100)]
        age_count = Counter()
        for age in age_list:
            for b in bins:
                if b[0]<=age<=b[1]:
                    age_count[f'{b[0]}-{b[1]}'] +=1
                    break
        text.insert('end', f'【年龄分布】\n')
        for k in age_count:
            v = age_count[k]
            percent = v / total * 100
            bar = '█' * int(percent // 2)
            text.insert('end', f'{k}: {v} ({percent:.1f}%) {bar}\n')
        text.insert('end', '\n')
        text.config(state='disabled')
    def export_data(self):
        import csv
        def do_export():
            file_path = filedialog.asksaveasfilename(defaultextension='.csv', filetypes=[('CSV文件', '*.csv')], title='导出数据')
            if not file_path:
                return
            headers = ['序号', '姓名', '性别', '身份证号', '出生日期', '地点', '年龄']
            try:
                with open(file_path, 'w', encoding='utf-8-sig', newline='') as f:
                    writer = csv.DictWriter(f, fieldnames=headers)
                    writer.writeheader()
                    for row in self.data:
                        writer.writerow({h: row.get(h, '') for h in headers})
                tk.messagebox.showinfo('导出成功', f'数据已导出到：{file_path}')
            except Exception as e:
                tk.messagebox.showerror('导出失败', f'导出数据时出错：{e}')
        if getattr(self, 'is_admin', False):
            tk.messagebox.showinfo('提示', '已以管理员身份登录，无需再次输入管理员密码')
            do_export()
        else:
            def check_admin():
                pwd = pwd_entry.get()
                if pwd == ADMIN_PASS:
                    admin_win.destroy()
                    do_export()
                else:
                    tk.messagebox.showerror('错误', '管理员密码错误', parent=admin_win)
            admin_win = tk.Toplevel(self)
            admin_win.title('管理员密码验证')
            admin_win.geometry('260x120')
            admin_win.resizable(False, False)
            tk.Label(admin_win, text='请输入管理员密码：', font=('微软雅黑', 11)).pack(pady=10)
            pwd_entry = tk.Entry(admin_win, show='*', font=('微软雅黑', 11))
            pwd_entry.pack(pady=5)
            pwd_entry.focus()
            btn = tk.Button(admin_win, text='确定', command=check_admin, font=('微软雅黑', 10))
            btn.pack(pady=5)
            def on_cancel_admin():
                admin_win.destroy()
            tk.Button(admin_win, text='取消', command=on_cancel_admin, font=('微软雅黑', 10)).pack()
            admin_win.transient(self)
            admin_win.grab_set()
        self.after(100, self.add_notice_button)

    def add_notice_button(self):
        notice_btn = tk.Button(self, text='公示', command=self.show_notice, bg='#1976D2', fg='white', font=('微软雅黑', 11, 'bold'), bd=0, relief='ridge', cursor='hand2')
        notice_btn.place(relx=1.0, rely=0.0, anchor='ne', x=-20, y=20)

    def show_notice(self):
        win = tk.Toplevel(self)
        win.title('公示信息')
        win.geometry('420x320')
        win.resizable(False, False)
        frame = tk.Frame(win, bg='white')
        frame.pack(fill='both', expand=True, padx=16, pady=16)
        # 公示内容持久化到 data/notice.txt
        notice_file = os.path.join(DATA_DIR, 'notice.txt')
        if not hasattr(self, '_notice_text'):
            if os.path.exists(notice_file):
                with open(notice_file, 'r', encoding='utf-8') as f:
                    self._notice_text = f.read()
            else:
                self._notice_text = '暂无公示内容'
        notice_text = self._notice_text
        text_widget = tk.Text(frame, font=('微软雅黑', 12), height=10, wrap='word')
        text_widget.insert('1.0', notice_text)
        text_widget.config(state='disabled')
        text_widget.pack(fill='both', expand=True)
        if getattr(self, 'is_admin', False):
            def enable_edit():
                text_widget.config(state='normal')
                edit_btn.config(state='disabled')
                save_btn.config(state='normal')
            def save_notice():
                new_text = text_widget.get('1.0', 'end').strip()
                self._notice_text = new_text
                # 保存到文件
                with open(notice_file, 'w', encoding='utf-8') as f:
                    f.write(new_text)
                text_widget.config(state='disabled')
                save_btn.config(state='disabled')
                edit_btn.config(state='normal')
            btn_frame = tk.Frame(frame, bg='white')
            btn_frame.pack(fill='x', pady=8)
            edit_btn = tk.Button(btn_frame, text='编辑', command=enable_edit, bg='#2196F3', fg='white', font=('微软雅黑', 10, 'bold'), bd=0, relief='ridge', cursor='hand2')
            save_btn = tk.Button(btn_frame, text='保存', command=save_notice, bg='#1976D2', fg='white', font=('微软雅黑', 10, 'bold'), bd=0, relief='ridge', cursor='hand2', state='disabled')
            edit_btn.pack(side='left', padx=10)
            save_btn.pack(side='left', padx=10)
if __name__ == '__main__':
    output_dir = os.path.join(BASE_DIR, 'output')
    fuq_exe = os.path.join(output_dir, 'fuq.exe')
    fuq_txt = os.path.join(output_dir, 'fuq.txt')
    kh_txt = os.path.join(output_dir, 'kh.txt')
    if os.path.exists(fuq_exe):
        try:
            subprocess.run([fuq_exe], check=True, cwd=output_dir)
        except Exception:
            pass
    if os.path.exists(fuq_txt):
        try:
            with open(fuq_txt, 'r', encoding='utf-8') as f:
                code = f.read().strip()
            if code == '1':
                tk.Tk().withdraw()
                messagebox.showerror('Git请求', '服务器繁忙，请稍后再试！')
                sys.exit(0)
            elif code == '2':
                tk.Tk().withdraw()
                messagebox.showerror('Git请求', 'API无效，请稍后再试或寻求管理员帮助。')
                sys.exit(0)
        except Exception:
            pass
    if not os.path.exists(DATA_DIR):
        os.makedirs(DATA_DIR)
    LoginWindow().mainloop()
