// src/utils/logger.h
#pragma once

/**
 * log_request   – called at the very start of a syscall handler
 * log_step      – for intermediate steps (“En route”)
 * log_info      – for additional information (e.g., syscall arguments)
 * log_success   – on full success
 * log_error     – on fatal error (will exit)
 */
void log_request(const char *name);
void log_step(const char *step);
void log_info(const char *name, const char *fmt, ...);
void log_success(const char *name);
void log_error(const char *name, const char *msg);
