<?php

function _hitsa_content_page_menu_nodes($main_menu_links)
{
    $menu_nodes = array();

    $school_type = variable_get('hitsa_school_type', HITSA_SCHOOL_GYMNASIUM);
    switch ($school_type) {
    case HITSA_SCHOOL_GYMNASIUM:
      $menu_nodes = _hitsa_content_page_gymnasium_nodes($main_menu_links);
      break;
    case HITSA_SCHOOL_VOCATIONAL:
      $menu_nodes = _hitsa_content_page_vocational_nodes($main_menu_links);
      break;
  }

    return $menu_nodes;
}

function _hitsa_content_page_gymnasium_nodes($main_menu_links)
{
    $t = get_t();
    return array(
    // Vastuvõtt

    array(
      'title' => array('et' => 'Õppesuunad', 'ru' => 'Направления обучения', 'en' => 'Subject fields'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_specialities',
      // Madis
    ),
    /*
      */
    array(
      'title' => array('et' => 'Vastuvõtu tingimused ja kord', 'ru' => 'Условия и порядок приема', 'en' => 'Admission terms and procedure'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 1,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Vajalikud dokumendid', 'ru' => 'Необходимые документы', 'en' => 'Required documents'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 2,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Gümnasisti vari', 'ru' => '«Тень» гимназиста', 'en' => 'Student shadow'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_simple',
    ),

    array(
      'title' => array('et' => 'Ettevalmistuskursused', 'ru' => 'Подготовительные курсы', 'en' => 'Preparatory courses'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_specialities',
      // Madis
    ),
    array(
      'title' => array('et' => 'Vastuvõtu ajakava', 'ru' => 'График приема', 'en' => 'Admission schedule'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 5,
      ),
      'cp_type' => 'cp_simple',
    ),
    // Õppetöö
    array(
      'title' => array('et' => 'Uue õppuri meelespea', 'ru' => 'Памятка новичка', 'en' => 'Student guide'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_simple',
    ),

    array(
      'title' => array('et' => 'Valikained', 'ru' => 'Предмет на выбор', 'en' => 'Elective subjects'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 1,
      ),
      'cp_type' => 'cp_specialities',
    ),

    array(
      'title' => array('et' => 'Tunniplaan', 'ru' => 'Расписание', 'en' => 'Timetable'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 2,
      ),
      'cp_type' => 'cp_specialities',

    ),
    /*
    array(
      'title' => array('et' => 'Õppetöö kalender', 'ru' => 'Календарь занятий', 'en' => 'Study calendar'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 3,
      ),
      // Madis

    ),
    */
    array(
      'title' => array('et' => 'Konsultatsiooniajad', 'ru' => 'Время консультаций', 'en' => 'Consultation times'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_contacts',
    ),
    array(
      'title' => array('et' => 'Uurimustöö', 'ru' => 'Научно-исследовательская работа', 'en' => 'Research'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 5,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Õpilastööde vormistamine', 'ru' => 'Оформление работ учеников', 'en' => 'Requirements for researchers'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Huvitavat lugemist', 'ru' => 'Увлекательного чтения', 'en' => 'Interesting reads'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 7,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Õppetöö korraldus', 'ru' => 'Организация занятий', 'en' => 'Study arrangement'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 8,
      ),
      'cp_type' => 'cp_simple',
    ),
    // Koolielu
    array(
      'title' => array('et' => 'Kodukord', 'ru' => 'Внутренний распорядок', 'en' => 'Rules of Procedure'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Koolibuss', 'ru' => 'Школьный автобус', 'en' => 'School bus'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 1,
      ),
      'cp_type' => 'cp_simple',
    ),

    array(
      'title' => array('et' => 'Õpilaskodu', 'ru' => 'Общежитие для учеников', 'en' => 'Boarding school'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 2,
      ),
      'cp_type' => 'cp_specialities',
    ),

    array(
      'title' => array('et' => 'Toitlustamine', 'ru' => 'Питание', 'en' => 'Catering'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Raamatukogu', 'ru' => 'Библиотека', 'en' => 'Library'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Tervisekabinet', 'ru' => 'Медпункт', 'en' => 'Health services'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 5,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Nõustamine', 'ru' => 'Консультирование', 'en' => 'Counselling'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_simple',
    ),
    /*
    array(
      'title' => array('et' => 'Huvitegevuse kalender', 'ru' => 'Календарь деятельности по интересам', 'en' => 'Events calendar'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 7,
      ),
      // Madis
    ),
    */
    array(
      'title' => array('et' => 'Huviringid', 'ru' => 'Кружки по интересам', 'en' => 'Hobby Groups'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 8,
      ),
      // Madis
      'cp_type' => 'cp_specialities',
    ),

    array(
      'title' => array('et' => 'Sport', 'ru' => 'Спорт', 'en' => 'Sports'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 9,
      ),
      'cp_type' => 'cp_specialities',
    ),

    array(
      'title' => array('et' => 'Toetused', 'ru' => 'Пособия', 'en' => 'Scholarships'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 10,
      ),
      'cp_type' => 'cp_specialities',
    ),
    // Meie koolist
    array(
      'title' => array('et' => 'Kooli väljaanded', 'ru' => 'Школьные издания', 'en' => 'Publications'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_specialities',
    ),

    array(
      'title' => array('et' => 'Virtuaaltuur', 'ru' => 'Виртуальный тур', 'en' => 'Virtual tour'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 1,
      ),
      // ????
    ),
    array(
      'title' => array('et' => 'Põhiväärtused', 'ru' => 'Высшие ценности', 'en' => 'Core values'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 2,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Traditsioonid', 'ru' => 'Традиции', 'en' => 'Traditions'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Kooli sümboolika', 'ru' => 'Школьная символика', 'en' => 'Brand and Logo'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Galerii', 'ru' => 'Галерея', 'en' => 'Gallery'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 5,
      ),
      // Madis
    ),
    array(
      'title' => array('et' => 'Tunnustused', 'ru' => 'Почетное признание', 'en' => 'Recognitions'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Õpilasesindus', 'ru' => 'Ученическое представительство', 'en' => 'Student council'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 7,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Õppenõukogu', 'ru' => 'Педагогический совет', 'en' => 'Teachers’ Council'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 8,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Hoolekogu', 'ru' => 'Попечительский совет', 'en' => 'Board of trustees'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 9,
      ),
      'cp_type' => 'cp_simple',
    ),

    array(
      'title' => array('et' => 'Koostöö', 'ru' => 'Сотрудничество', 'en' => 'Collaboration'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 10,
      ),
      'cp_type' => 'cp_specialities',
    ),

    array(
      'title' => array('et' => 'Vilistlased', 'ru' => 'Выпускники', 'en' => 'Graduates'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 11,
      ),
      'cp_type' => 'cp_simple',
    ),

    array(
      'title' => array('et' => 'Tööpakkumised', 'ru' => 'Предложения работы', 'en' => 'Vacancies'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 12,
      ),
      'cp_type' => 'cp_specialities',
    ),

    array(
      'title' => array('et' => 'Arengukava', 'ru' => 'План развития', 'en' => 'Development plan'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 13,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Põhimäärus', 'ru' => 'Устав', 'en' => 'Statutes'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 14,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Eeskirjad', 'ru' => 'Документы', 'en' => 'Documents'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 15,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Töötasustamise alused', 'ru' => 'Заработная плата', 'en' => 'Salary'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 16,
      ),
      'cp_type' => 'cp_simple',
    ),

  );
}

function _hitsa_content_page_vocational_nodes($main_menu_links)
{
    $t = get_t();
    $menu_links = array(
    // Sisseastumine
    /*
    array(
      'title' => array('et' => 'Erialad', 'ru' => 'Специальности', 'en' => 'Curriculum'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 0,
      ),
      // Madis
    ),
    */

    array(
      'title' => array('et' => 'Erialad', 'ru' => 'Специальности', 'en' => 'Curriculum'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Vastuvõtt', 'ru' => 'Прием', 'en' => 'Admission'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 1,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Töökohapõhine õpe', 'ru' => 'Профессиональное обучение на месте работы', 'en' => 'Work-based studies'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 2,
      ),
      'cp_type' => 'cp_simple',
    ),

    array(
      'title' => array('et' => 'Ettevalmistuskursused', 'ru' => 'Подготовительные курсы', 'en' => 'Preparatory courses'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_specialities',
    ),
    /*
    array(
      'title' => array('et' => 'Ettevalmistuskursused', 'ru' => 'Подготовительные курсы', 'en' => 'Preparatory courses'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 3,
      ),
      // Madis
    ),
    */
    array(
      'title' => array('et' => 'Avatud uste päev', 'ru' => 'День открытых дверей', 'en' => 'Open house days'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Tudengi vari', 'ru' => '«Тень» студента', 'en' => 'Student shadow'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 5,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Mittestatsionaarne õpe', 'ru' => 'Hестационарной формы обучения', 'en' => 'Non-stationary studies'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Kaugõpe', 'ru' => 'Заочное обучение', 'en' => 'Distance learning'),
      'menu' => array(
        'plid' => $main_menu_links['Admission'],
        'weight' => 7,
      ),
      'cp_type' => 'cp_simple',
    ),
    // Õppetöö
    /*
    array(
      'title' => array('et' => 'Õppetöö kalender', 'ru' => 'Календарь занятий', 'en' => 'Study calendar'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 0,
      ),
      // Madis

    ), */
    array(
      'title' => array('et' => 'Tunniplaan', 'ru' => 'Расписание', 'en' => 'Timetable'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 1,
      ),
      // ????
    ),
    array(
      'title' => array('et' => 'VÕTA', 'ru' => 'VÕTA', 'en' => 'APEL'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 2,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Lõpetamine', 'ru' => 'Градуировать', 'en' => 'Graduation'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Õpilastööde vormistamine', 'ru' => 'Оформление работ учеников', 'en' => 'Requirements for researchers'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Õpiränne', 'ru' => 'Учебная миграция', 'en' => 'Learning mobility'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 5,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Praktika', 'ru' => 'Практика', 'en' => 'Internship'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Vabaained', 'ru' => 'Факультативные предметы', 'en' => 'Elective courses'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 7,
      ),
      'cp_type' => 'cp_specialities',
      // Madis
    ),
    array(
      'title' => array('et' => 'Valikained', 'ru' => 'Предмет на выбор', 'en' => 'Elective subjects'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 8,
      ),
      'cp_type' => 'cp_specialities',
      // Madis

    ),
    /*
    array(
      'title' => array('et' => 'Vabaained', 'ru' => 'Факультативные предметы', 'en' => 'Elective courses'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 7,
      ),
      // Madis
    ),
    array(
      'title' => array('et' => 'Valikained', 'ru' => 'Предмет на выбор', 'en' => 'Elective subjects'),
      'menu' => array(
        'plid' => $main_menu_links['Studies'],
        'weight' => 8,
      ),
      // Madis

    ),
    */
    // Koolielu
    array(
      'title' => array('et' => 'Kodukord', 'ru' => 'Внутренний распорядок', 'en' => 'Rules of Procedure'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_simple',
    ),
    /*
    */

    array(
      'title' => array('et' => 'Majutus', 'ru' => 'Проживание', 'en' => 'Accommodation'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 1,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Toitlustamine', 'ru' => 'Питание', 'en' => 'Catering'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 2,
      ),
      // Madis
    ),
    array(
      'title' => array('et' => 'Raamatukogu', 'ru' => 'Библиотека', 'en' => 'Library'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_simple',
    ),
    /*
    array(
      'title' => array('et' => 'Huvitegevuse kalender', 'ru' => 'Календарь деятельности по интересам', 'en' => 'Events calendar'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 4,
      ),
      // Madis
    ),
    array(
      'title' => array('et' => 'Huvitegevused', 'ru' => 'Деятельность по интересам', 'en' => 'Hobby activities'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 5,
      ),
      // Madis

    ),
    array(
      'title' => array('et' => 'Sportimisvõimalused', 'ru' => 'Возможности для занятий спортом', 'en' => 'Sport facilities'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_specialities',
    ),
    */

    array(
      'title' => array('et' => 'Huvitegevused', 'ru' => 'Деятельность по интересам', 'en' => 'Hobby activities'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 5,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Sportimisvõimalused', 'ru' => 'Возможности для занятий спортом', 'en' => 'Sport facilities'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Nõustamine', 'ru' => 'Консультирование', 'en' => 'Counselling'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 7,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Toetused', 'ru' => 'Пособия', 'en' => 'Scholarships'),
      'menu' => array(
        'plid' => $main_menu_links['Student Life'],
        'weight' => 8,
      ),
      'cp_type' => 'cp_specialities',
    ),

    // Täiendusõpe

    array(
      'title' => array('et' => 'Täiendusõppe toetused', 'ru' => 'Пособия для повышения квалификации', 'en' => 'Training Scholarships'),
      'menu' => array(
        'plid' => $main_menu_links['Trainings'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'E-kursused', 'ru' => 'Электронные курсы', 'en' => 'E-courses'),
      'menu' => array(
        'plid' => $main_menu_links['Trainings'],
        'weight' => 1,
      ),
      // Madis
    ),
    array(
      'title' => array('et' => 'Kutseeksamid', 'ru' => 'Квалификационные экзамены', 'en' => 'Certification exams'),
      'menu' => array(
        'plid' => $main_menu_links['Trainings'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Tellitavad koolitused', 'ru' => 'Заказные тренинги', 'en' => 'Ordered trainings'),
      'menu' => array(
        'plid' => $main_menu_links['Trainings'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_specialities',

    ),
    // Teenused
    /* Added through custom code */
    // Meie koolist
    array(
      'title' => array('et' => 'Kooli väljaanded', 'ru' => 'Школьные издания', 'en' => 'Publications'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 0,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Põhiväärtused', 'ru' => 'Высшие ценности', 'en' => 'Core values'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 2,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Traditsioonid', 'ru' => 'Традиции', 'en' => 'Traditions'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 3,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Kooli sümboolika', 'ru' => 'Школьная символика', 'en' => 'Brand and Logo'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 4,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Galerii', 'ru' => 'Галерея', 'en' => 'Gallery'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 5,
      ),
      // Madis
    ),
    array(
      'title' => array('et' => 'Tunnustused', 'ru' => 'Почетное признание', 'en' => 'Recognitions'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 6,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Õpilasesindus', 'ru' => 'Ученическое представительство', 'en' => 'Student council'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 7,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Kooli nõukogu', 'ru' => 'Педагогический совет', 'en' => 'Teachers’ Council'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 8,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Nõunike kogu', 'ru' => 'Попечительский совет', 'en' => 'Board of trustees'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 9,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Koostöö ja projektid', 'ru' => 'Сотрудничество', 'en' => 'Collaboration and projects'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 10,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Vilistlased', 'ru' => 'Выпускники', 'en' => 'Graduates'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 11,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Tööpakkumised', 'ru' => 'Предложения работы', 'en' => 'Vacancies'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 12,
      ),
      'cp_type' => 'cp_specialities',
    ),
    array(
      'title' => array('et' => 'Arengukava', 'ru' => 'План развития', 'en' => 'Development plan'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 13,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Põhimäärus', 'ru' => 'Устав', 'en' => 'Statutes'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 14,
      ),
      'cp_type' => 'cp_simple',
    ),
    array(
      'title' => array('et' => 'Eeskirjad', 'ru' => 'Документы', 'en' => 'Documents'),
      'menu' => array(
        'plid' => $main_menu_links['About us'],
        'weight' => 15,
      ),
      'cp_type' => 'cp_simple',
    ),
  );

    return $menu_links;
}
