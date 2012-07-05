<?php

/**
 * Save unilogin id
 * 
 * @param integer $uid
 *   Drupal user id.
 * @param string $unilogin_id
 *   Unilogin id.
 * @return void
 */
function _unilogin_db_save_unilogin_id($uid, $unilogin_id){
  if(empty($uid) || empty($unilogin_id)) return;
  $Uni = new stdClass();
  $Uni->uid = $uid;
  $Uni->unilogin_id = $unilogin_id;
  $unilogin_db = _unilogin_db_load_unilogin_id_by_uid($uid);
  if(!$unilogin_db){
    drupal_write_record('unilogin_users', $Uni);
  }elseif($unilogin_db != $unilogin_id){
    drupal_write_record('unilogin_users', $Uni, 'uid');
  }
}

/**
 * Get user id from a unilogin id.
 * 
 * @param string $unilogin_id
 * @return mixed
 *   integer/FALSE
 */
function _unilogin_db_load_uid_by_unilogin_id($unilogin_id){
  if(empty($unilogin_id)) return;
  return db_result(
    db_query("SELECT uid FROM {unilogin_users} WHERE unilogin_id = '%s'", $unilogin_id)
  );
}

/**
 * Get unilogin id from user id.
 * 
 * @param integer $uid
 * @return mixed
 *   string/FALSE
 */
function _unilogin_db_load_unilogin_id_by_uid($uid){
  if(empty($uid)) return;
  return db_result(
    db_query("SELECT unilogin_id FROM {unilogin_users} WHERE uid = %d", $uid)
  );
}

function _unilogin_db_load_session_id_by_unilogin_id($unilogin_id){
  if(empty($unilogin_id)) return;
  return db_result(
    db_query("SELECT sid FROM {unilogin_sessions} WHERE unilogin_id = '%s'", $unilogin_id)
  );
}

function _unilogin_db_load_session_id_by_user_id($uid){
  if(empty($uid)) return;
  return db_result(
    db_query("SELECT sid FROM {sessions} WHERE uid= %d", $uid)
  );
}

function _unilogin_db_load_session_id_by_unilog_id($unilogin_id){
  if(empty($unilogin_id)) return;
  return db_result(
    db_query("SELECT sid FROM {unilogin_sessions} WHERE unilogin_id= '%s'", $unilogin_id)
  );
}

function _unilogin_db_delete_session_entry_by_session_id($sid){
  if(empty($sid)) return;
  db_query("DELETE FROM {unilogin_sessions} WHERE sid = '%s'", $sid);
}


function _unilogin_db_save_session($unilogin_id, $user){
  if(!_unilogin_db_load_session_id_by_unilogin_id($unilogin_id)){
    $Session = new stdClass();
    $Session->sid = $user->sid;
    $Session->unilogin_id = $unilogin_id;
    drupal_write_record('unilogin_sessions', $Session);
    return TRUE;
  }
  return FALSE;
}
