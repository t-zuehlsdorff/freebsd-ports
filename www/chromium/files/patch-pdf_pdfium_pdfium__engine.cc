--- pdf/pdfium/pdfium_engine.cc.orig	2016-05-11 19:02:25 UTC
+++ pdf/pdfium/pdfium_engine.cc
@@ -121,7 +121,7 @@ std::vector<uint32_t> GetPageNumbersFrom
   return page_numbers;
 }
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
 
 PP_Instance g_last_instance_id;
 
@@ -507,7 +507,7 @@ bool InitializeSDK() {
   config.m_v8EmbedderSlot = gin::kEmbedderPDFium;
   FPDF_InitLibraryWithConfig(&config);
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   // Font loading doesn't work in the renderer sandbox in Linux.
   FPDF_SetSystemFontInfo(&g_font_info);
 #endif
@@ -620,7 +620,7 @@ PDFiumEngine::PDFiumEngine(PDFEngine::Cl
   IFSDK_PAUSE::user = nullptr;
   IFSDK_PAUSE::NeedToPauseNow = Pause_NeedToPauseNow;
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   // PreviewModeClient does not know its pp::Instance.
   pp::Instance* instance = client_->GetPluginInstance();
   if (instance)
@@ -1330,7 +1330,7 @@ pp::Buffer_Dev PDFiumEngine::PrintPagesA
     FPDF_ClosePage(pdf_page);
   }
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   g_last_instance_id = client_->GetPluginInstance()->pp_instance();
 #endif
 
@@ -2688,7 +2688,7 @@ bool PDFiumEngine::ContinuePaint(int pro
   DCHECK_LT(static_cast<size_t>(progressive_index), progressive_paints_.size());
   DCHECK(image_data);
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   g_last_instance_id = client_->GetPluginInstance()->pp_instance();
 #endif
 
@@ -3142,7 +3142,7 @@ void PDFiumEngine::SetCurrentPage(int in
     FORM_DoPageAAction(old_page, form_, FPDFPAGE_AACTION_CLOSE);
   }
   most_visible_page_ = index;
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
     g_last_instance_id = client_->GetPluginInstance()->pp_instance();
 #endif
   if (most_visible_page_ != -1 && called_do_document_action_) {
